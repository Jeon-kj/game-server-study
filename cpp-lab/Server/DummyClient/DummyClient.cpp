#include "pch.h"
#include <iostream>
#include <thread>
#include <chrono>

#include <WinSock2.h>
#include <mswsock.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

const int32 BUFSIZE = 1000;

struct Session
{
	SOCKET socket = INVALID_SOCKET;
	char recvBuffer[BUFSIZE] = {};
	int32 recvBytes = 0;
	int32 sendBytes = 0;
};

int main()
{
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	SOCKET clientSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET)
		return 0;


	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = AF_INET;
	::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
	serverAddr.sin_port = htons(7777);

	if (::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		return 0;

	cout << "Connected to Server!" << endl;

	u_long on = 1;
	if (::ioctlsocket(clientSocket, FIONBIO, &on) == SOCKET_ERROR)
		return 0;

	char sendBuffer[100] = "Hello World";


	while (true)
	{
		int32 sendLen = ::send(clientSocket, sendBuffer, sizeof(sendBuffer), 0);
		if (sendLen == SOCKET_ERROR)
		{
			if (::WSAGetLastError() == WSAEWOULDBLOCK)
				continue;

			break;
		}

		cout << "Send Data Len = " << sendLen << endl;
		cout << "Send Data : " << sendBuffer << endl;
		//this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	::closesocket(clientSocket);
	::WSACleanup();

	return 0;
}