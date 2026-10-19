#include "pch.h"
#include "TcpClient.h"

#include <string>

SOCKET ConnectToServer()
{
	// client Socket 생성
	SOCKET clientSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET)
	{
		int32 errorCode = ::WSAGetLastError();
		cout << "Socket Error: " << errorCode << endl;
		return INVALID_SOCKET;
	}

	// server address connect
	SOCKADDR_IN serverAddr{ 0 };
	serverAddr.sin_family = AF_INET;
	::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
	serverAddr.sin_port = htons(9999);

	if (::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		int32 errorCode = ::WSAGetLastError();
		cout << "Connect Error: " << errorCode << endl;
		::closesocket(clientSocket);
		return INVALID_SOCKET;
	}

	return clientSocket;
}

void RunSendLoop(SOCKET clientSocket)
{
	while (true)
	{
		string msg = "";
		cout << "Enter the Message: ";
		cin >> msg;
		std::vector<char> sendMsg(msg.begin(), msg.end());
		sendMsg = MakePacket(sendMsg, static_cast<uint16>(Type::TextMessage));

		int32 sendLen = ::send(clientSocket, sendMsg.data(), sendMsg.size(), 0);
		if (sendLen == SOCKET_ERROR)
		{
			int32 errorCode = ::WSAGetLastError();
			cout << "Send Error: " << errorCode << endl;
			return;
		}
	}
}