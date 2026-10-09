#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>
#include "ThreadManager.h"

#include <WinSock2.h>
#include <mswsock.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

enum ParseResult
{
	Complete,
	NeedMore,
	Invalid
};
bool SendAll(SOCKET clientSocket, char* sendBuffer, int32 length)
{
	int32 progress = 0;

	while (length != 0)
	{
		int32 resultCode = ::send(clientSocket, sendBuffer + progress, length, 0);
		if (resultCode == SOCKET_ERROR)
		{
			int32 errCode = ::WSAGetLastError();
			cout << "Send ErrorCode : " << errCode << endl;
			return false;
		}

		if (resultCode == 0)
		{
			cout << "Disconnected" << endl;
			return false;
		}

		cout << "send scope : " << progress << "~" << progress + resultCode - 1 << endl;
		cout << "send data : ";
		cout.write(sendBuffer + progress, resultCode);
		cout << endl;

		progress += resultCode;
		length -= resultCode;
	}

	return true;
}

int32 Recv(SOCKET clientSocket, char* recvBuffer, int32 length)
{
	int32 recvLen = ::recv(clientSocket, recvBuffer, length, 0);

	if (recvLen == SOCKET_ERROR)
	{
		int32 errCode = ::WSAGetLastError();
		cout << "Recv ErrorCode : " << errCode << endl;
		return -1;
	}
	else if (recvLen == 0)
	{
		cout << "Disconnected" << endl;
		return 0;
	}

	cout << "Receive Data! - data : ";
	cout.write(recvBuffer, recvLen);
	cout << endl;

	cout << "Receive Data! - length : " << recvLen << endl;

	return recvLen;
}

char* PackMessage(char* msg, int32& dataLen)
{
	if (dataLen < 0 || dataLen > 1024-4)
		return nullptr;

	dataLen = dataLen + 4;
	char* sendData = new char[dataLen];

	sendData[0] = static_cast<char>((dataLen >> 8) & 0xFF);
	sendData[1] = static_cast<char>(dataLen & 0xFF);

	sendData[2] = 0;
	sendData[3] = 1; // type 미정

	memcpy(sendData + 4, msg, dataLen-4);

	return sendData;
}

ParseResult UnpackMessage(char* recvBuffer, int32& recvLen)
{
	if (recvLen < 4)
	{
		cout << "NeedMore" << endl; // 헤더 부족
		return NeedMore;
	}

	const auto* bytes = reinterpret_cast<const unsigned char*>(recvBuffer);

	int32 header_len = (bytes[0] << 8) | bytes[1];
	int32 header_type = (bytes[2] << 8) | bytes[3];
	
	if (header_len < 4 || header_len > 1024)
	{
		cout << "Invalid" << endl;
		return Invalid;
	}

	if (recvLen < header_len)
	{
		cout << "NeedMore" << endl;
		return NeedMore;
	}

	cout << "Complete" << endl;

	memmove(recvBuffer, recvBuffer + 4, header_len - 4);
	recvLen = header_len - 4;

	return Complete;
}

int main()
{
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET)
	{
		int32 errCode = ::WSAGetLastError();
		cout << "Socket ErrorCode : " << errCode << endl;
		::WSACleanup();
		return 0;
	}

	// 나의 주소는?
	SOCKADDR_IN serverAddr;
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY); // 알아서 해줘 (가능한 주소 모두 연결?)
	serverAddr.sin_port = htons(7777);

	if (::bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		int32 errCode = ::WSAGetLastError();
		cout << "Bind ErrorCode : " << errCode << endl;
		::closesocket(listenSocket);
		::WSACleanup();
		return 0;
	}

	if(::listen(listenSocket, 10) == SOCKET_ERROR) // 10 = 대기 가능한 소켓 수
	{
		int32 errCode = ::WSAGetLastError();
		cout << "Listen ErrorCode : " << errCode << endl;
		::closesocket(listenSocket);
		::WSACleanup();
		return 0;
	}

	// --------------------------
	
	while (true)
	{
		SOCKADDR_IN clientAddr;
		::memset(&clientAddr, 0, sizeof(clientAddr));
		int32 addrLen = sizeof(clientAddr);

		// 두번째 매개변수부터는 nullptr 가능
		// 연결이 된 순간부터 운영체제가 연결 정보를 관리하기 때문에 주소를 따로 받지 않아도 통신 가능
		// 심지어 나중에 SOCKET변수로부터 추출할 수도 있음
		SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
		if (clientSocket == INVALID_SOCKET)
		{
			int32 errCode = ::WSAGetLastError();
			cout << "Accept ErrorCode : " << errCode << endl;
			::closesocket(listenSocket);
			::WSACleanup();
			return 0;
		}

		char ipAddress[16];
		::inet_ntop(AF_INET, &clientAddr.sin_addr, ipAddress, sizeof(ipAddress));
		cout << "Client Connected! IP = " << ipAddress << endl;

		//TODO
		while (true)
		{
			char recvBuffer[1000];
			int32 recvLen = Recv(clientSocket, recvBuffer, sizeof(recvBuffer));
			if (recvLen <= 0)
				break;

			int32 result = UnpackMessage(recvBuffer, recvLen);
			if (result != Complete)
				break;

			char* sendBuffer = PackMessage(recvBuffer, recvLen);
			if (sendBuffer == nullptr)
			{
				cout << "Packaging Error" << endl;
				break;
			}

			bool flag = SendAll(clientSocket, sendBuffer, recvLen);
			delete[] sendBuffer;
			if (!flag)
				break;
		}

		::closesocket(clientSocket);
	}

	// --------------------------

	// 윈속 종료
	::closesocket(listenSocket);
	::WSACleanup();
}