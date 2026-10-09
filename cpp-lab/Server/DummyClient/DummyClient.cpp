#include "pch.h"
#include <iostream>
#include <thread>

#include <WinSock2.h>
#include <mswsock.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSAData wsaData;
    if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        return 0;

    SOCKET clientSocket = ::socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET)
    {
        int32 errCode = ::WSAGetLastError();
        cout << "Socket Error Code : " << errCode << endl;
        return 0;
    }

    SOCKADDR_IN serverAddr; // IPv4
    ::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    ::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
    serverAddr.sin_port = ::htons(7777);

    if (::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        int32 errCode = ::WSAGetLastError();
        cout << "Connect ErrorCode : " << errCode << endl;
        return 0;
    }

    // --------------------------
    // 연결 성공! 이제부터 데이터 송수신 가능

    cout << "Connected To Server!" << endl;

    while (true)
    {
        // TODO
        char sendBuffer[100] = "HelloWorld!";

        int32 resultCode = ::send(clientSocket, sendBuffer, sizeof(sendBuffer), 0);
        if (resultCode == SOCKET_ERROR)
        {
            int32 errCode = ::WSAGetLastError();
            cout << "Send ErrorCode : " << errCode << endl;
            return 0;
        }

        cout << "Send Data! data = " << sendBuffer << endl;
        cout << "Send Data! length = " << sizeof(sendBuffer) << endl;

        char recvBuffer[1000];

        int32 recvLen = ::recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
        if (recvLen <= 0)
        {
            int32 errCode = ::WSAGetLastError();
            cout << "Recv ErrorCode : " << errCode << endl;
            return 0;
        }

        cout << "Receive Data! - data : " << recvBuffer << endl;
        cout << "Receive Data! - length : " << sizeof(recvBuffer) << endl;

        this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    // --------------------------

    // 소켓 리소스 반환
    ::closesocket(clientSocket);

    // 윈속 종료 
    ::WSACleanup();   
}