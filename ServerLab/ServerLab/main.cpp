#include "pch.h"
#include "TcpServer.h"

int main()
{
	// wsaData 초기화
	WSADATA wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 1;
	
	SOCKET listenSocket = CreateListenSocket();
	if (listenSocket == INVALID_SOCKET)
	{
		::WSACleanup();
		return 1;
	}

	RunAcceptLoop(listenSocket);
	
	// clear
	::closesocket(listenSocket);
	::WSACleanup();
	return 0;
}