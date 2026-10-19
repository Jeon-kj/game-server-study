#pragma once

#include <WinSock2.h>
#include <vector>
#include <array>

#include "Types.h"

class Session
{
public:
	Session() : _socket(INVALID_SOCKET)
	{
		_recvBuffer.reserve(1000);
	}

	~Session()
	{
		_socket = INVALID_SOCKET;
		::closesocket(_socket);
	}

	Session(SOCKET socket) : _socket(socket)
	{
		_recvBuffer.reserve(1000);
	}

public:
	SOCKET GetSocket() { return _socket; }
	const std::vector<char>& GetRecvBuffer() { return _recvBuffer; }
	
	int32 Recv();

	void ConsumeRecvBuffer(uint16 packLen) { _recvBuffer.erase(_recvBuffer.begin(), _recvBuffer.begin() + packLen); }

private:
	SOCKET _socket;
	std::vector<char> _recvBuffer;
	std::array<char, 4096> _tempBuffer;
};
