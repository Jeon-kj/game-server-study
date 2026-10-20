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

	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET)
	{
		::WSACleanup();
		return 0;
	}

	SOCKADDR_IN serverAddr{ 0 };
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(7777);

	if (::bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		::closesocket(listenSocket);
		::WSACleanup();
		return 0;
	}

	if (::listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		::closesocket(listenSocket);
		::WSACleanup();
		return 0;
	}

	cout << "Accept" << endl;

	vector<WSAEVENT> wsaEvents;
	wsaEvents.reserve(64);
	vector<Session> sessions;
	sessions.reserve(100);

	WSAEVENT listenEvent = ::WSACreateEvent();
	wsaEvents.push_back(listenEvent);
	sessions.push_back(Session{ listenSocket });
	if (::WSAEventSelect(listenSocket, listenEvent, FD_ACCEPT | FD_CLOSE) == SOCKET_ERROR)
	{
		::closesocket(listenSocket);
		::WSACleanup();
		return 0;
	}

	while (true)
	{
		// 반환값 = WSA_WAIT_EVENT_0 + 이벤트 배열 인덱스
		int32 index = ::WSAWaitForMultipleEvents(wsaEvents.size(), &wsaEvents[0], FALSE, WSA_INFINITE, FALSE);
		if (index == WSA_WAIT_FAILED)
			continue;

		index -= WSA_WAIT_EVENT_0;

		WSANETWORKEVENTS networkEvents;
		if (::WSAEnumNetworkEvents(sessions[index].socket, wsaEvents[index], &networkEvents) == SOCKET_ERROR)
			continue;

		if (networkEvents.lNetworkEvents & FD_ACCEPT)
		{
			if (networkEvents.iErrorCode[FD_ACCEPT_BIT] != 0)
				continue;

			SOCKADDR_IN clientAddr;
			int32 addrLen = sizeof(clientAddr);

			SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
			if (clientSocket != INVALID_SOCKET)
			{
				cout << "Client Connected!" << endl;
				WSAEVENT clientEvent = ::WSACreateEvent();
				wsaEvents.push_back(clientEvent);
				sessions.push_back(Session{ clientSocket });
				if (::WSAEventSelect(clientSocket, clientEvent, FD_READ | FD_WRITE | FD_CLOSE) == SOCKET_ERROR)
					return 0;
			}
			else
			{
				int32 err = ::WSAGetLastError();
				if (err == WSAEWOULDBLOCK)
					continue;

				
				cout << "Accept Error: " << err << endl;
				continue;
			}

			
		}

		if (networkEvents.lNetworkEvents & FD_READ || networkEvents.lNetworkEvents & FD_WRITE)
		{
			// Error-Check
			if ((networkEvents.lNetworkEvents & FD_READ) && (networkEvents.iErrorCode[FD_READ_BIT] != 0))
				continue;
			// Error-Check
			if ((networkEvents.lNetworkEvents & FD_WRITE) && (networkEvents.iErrorCode[FD_WRITE_BIT] != 0))
				continue;

			Session& s = sessions[index];

			if (s.recvBytes == 0)
			{
				int32 recvLen = ::recv(s.socket, &s.recvBuffer[s.recvBytes], BUFSIZE - s.recvBytes, 0);
				if (recvLen == SOCKET_ERROR)
				{
					if (::WSAGetLastError() == WSAEWOULDBLOCK)
						continue;

					// 오류 처리
					::closesocket(s.socket);
					::WSACloseEvent(wsaEvents[index]);

					sessions.erase(sessions.begin() + index);
					wsaEvents.erase(wsaEvents.begin() + index);
					continue;
				}

				if (recvLen == 0)
				{
					// 정상 연결 해제 요청
					::closesocket(s.socket);
					::WSACloseEvent(wsaEvents[index]);

					sessions.erase(sessions.begin() + index);
					wsaEvents.erase(wsaEvents.begin() + index);
					continue;
				}

				s.recvBytes += recvLen;
				cout << "recv Data : " << s.recvBuffer << endl;
			}
			
			if (s.recvBytes > s.sendBytes)
			{
				// Echo
				int32 sendLen = ::send(s.socket, &s.recvBuffer[s.sendBytes], s.recvBytes - s.sendBytes, 0);
				if (sendLen == SOCKET_ERROR)
				{
					if (::WSAGetLastError() == WSAEWOULDBLOCK)
						continue;

					// 오류 처리
					::closesocket(s.socket);
					::WSACloseEvent(wsaEvents[index]);

					sessions.erase(sessions.begin() + index);
					wsaEvents.erase(wsaEvents.begin() + index);
					continue;
				}

				s.sendBytes += sendLen;
				cout << "send Data Len : " << s.sendBytes << endl;
				if (s.sendBytes == s.recvBytes)
				{
					s.sendBytes = 0;
					s.recvBytes = 0;
				}
			}			
		}

		if (networkEvents.lNetworkEvents & FD_CLOSE)
		{
			int32 err = networkEvents.iErrorCode[FD_CLOSE_BIT];

			if (err != 0)
				cout << "FD_CLOSE Error : " << err << endl;

			// TODO : Remove Socket
			::closesocket(sessions[index].socket);
			::WSACloseEvent(wsaEvents[index]);

			sessions.erase(sessions.begin() + index);
			wsaEvents.erase(wsaEvents.begin() + index);
		}
	}

	for (int32 i = 0; i < sessions.size(); i++)
	{
		::closesocket(sessions[i].socket);
		::WSACloseEvent(wsaEvents[i]);
	}
	sessions.clear();
	wsaEvents.clear();
	
	::WSACleanup();

	return 0;
}