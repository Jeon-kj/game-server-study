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

	vector<Session> sessions;
	sessions.reserve(100);
	sessions.push_back(Session{ clientSocket });

	fd_set reads;
	fd_set writes;

	while (true)
	{
		if (sessions.empty())
			break;

		FD_ZERO(&reads);
		FD_ZERO(&writes);

		for (Session& s : sessions)
		{
			if (s.sendBytes < sizeof(sendBuffer))
				FD_SET(s.socket, &writes);
			else
				FD_SET(s.socket, &reads);
		}

		int32 retVal = ::select(0, &reads, &writes, nullptr, nullptr);
		if (retVal == SOCKET_ERROR)
			break;

		for (auto it = sessions.begin(); it != sessions.end();)
		{
			Session& s = *it;
			if (FD_ISSET(s.socket, &reads))
			{
				int32 recvLen = ::recv(s.socket, &s.recvBuffer[s.recvBytes], s.sendBytes-s.recvBytes, 0);
				if (recvLen == SOCKET_ERROR)
				{
					if (::WSAGetLastError() == WSAEWOULDBLOCK)
					{
						++it;
						continue;
					}

					// TODO: sessions 제거
					::closesocket(s.socket);
					it = sessions.erase(it);
					continue;
				}

				if (recvLen == 0)
				{
					// 정상적인 연결 종료
					::closesocket(s.socket);
					it = sessions.erase(it);
					continue;
				}

				s.recvBytes += recvLen;
				if (s.recvBytes == s.sendBytes)
				{
					s.recvBytes = 0;
					s.sendBytes = 0;
				}
			}

			if (FD_ISSET(s.socket, &writes))
			{
				int32 sendLen = ::send(s.socket, sendBuffer+s.sendBytes, sizeof(sendBuffer)-s.sendBytes, 0);
				if (sendLen == SOCKET_ERROR)
				{
					if (::WSAGetLastError() == WSAEWOULDBLOCK)
					{
						++it;
						continue;
					}

					// TODO: sessions 제거
					::closesocket(s.socket);
					it = sessions.erase(it);
					continue;
				}

				s.sendBytes += sendLen;
				
				cout << "Send Data ! Len = " << sizeof(sendBuffer) << endl;
				cout << "Send Data : " << sendBuffer << endl;
			}
			++it;
		}

		this_thread::sleep_for(std::chrono::seconds(1));
	}
}