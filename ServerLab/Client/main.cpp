#include "pch.h"
#include "TcpClient.h"

int main()
{
	// wsaData 초기화
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	SOCKET clientSocket = ConnectToServer();
	if (clientSocket == INVALID_SOCKET)
	{
		::WSACleanup();
		return 1;
	}

	RunSendLoop(clientSocket);

	// disconnect
	::closesocket(clientSocket);
	::WSACleanup();
}