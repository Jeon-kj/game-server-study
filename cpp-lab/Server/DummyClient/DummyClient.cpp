#include "pch.h"
#include <iostream>
#include <thread>

#include <WinSock2.h>
#include <mswsock.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

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
        ::WSACleanup();
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
        ::closesocket(clientSocket);
        ::WSACleanup();
        return 0;
    }

    // --------------------------
    // 연결 성공! 이제부터 데이터 송수신 가능

    cout << "Connected To Server!" << endl;

    while (true)
    {
        // TODO
        char sendBuffer[] = "Hello";

        bool flag = SendAll(clientSocket, sendBuffer, sizeof(sendBuffer)-1);
        if (!flag)
            break;

        char recvBuffer[1000];

        int32 recvLen = Recv(clientSocket, recvBuffer, sizeof(recvBuffer));
        if (recvLen <= 0)
            break;

        this_thread::sleep_for(std::chrono::milliseconds(100000));
    }

    // --------------------------

    // 소켓 리소스 반환
    ::closesocket(clientSocket);

    // 윈속 종료 
    ::WSACleanup();   
}