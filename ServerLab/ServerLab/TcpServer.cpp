#include "pch.h"
#include "TcpServer.h"
#include "ClientSession.h"

SOCKET CreateListenSocket()
{
	// listen Socket 생성
	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET)
	{
		int32 errorCode = ::WSAGetLastError();
		cout << "Socket Error: " << errorCode << endl;
		return INVALID_SOCKET;
	}

	// 주소랑 Bind
	SOCKADDR_IN serverAddr{ 0 };
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(9999);

	if (::bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		int32 errorCode = ::WSAGetLastError();
		cout << "Bind Error: " << errorCode << endl;
		::closesocket(listenSocket);
		return INVALID_SOCKET;
	}

	//listen
	if (::listen(listenSocket, 10) == SOCKET_ERROR)
	{
		int32 errorCode = ::WSAGetLastError();
		cout << "listen error: " << errorCode << endl;
		::closesocket(listenSocket);
		return INVALID_SOCKET;
	}

	return listenSocket;
}

void RunAcceptLoop(SOCKET listenSocket)
{
	while (true)
	{
		// accept
		SOCKADDR_IN clientAddr{ 0 };
		int32 addrLen = sizeof(clientAddr);

		SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
		if (clientSocket == INVALID_SOCKET)
		{
			int32 errorCode = ::WSAGetLastError();
			cout << "accept error: " << errorCode << endl;
			return;
		}

		Session session(clientSocket);

		char ipAddress[16];
		::inet_ntop(AF_INET, &clientAddr.sin_addr, ipAddress, sizeof(ipAddress));
		cout << "Client Connected. IP: " << ipAddress << endl;

		HandleClient(session);

		::closesocket(clientSocket);
	}
}
