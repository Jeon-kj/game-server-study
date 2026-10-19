#include "Session.h"
#include "pch.h"

int32 Session::Recv()
{
	int32 recvLen = ::recv(_socket, _tempBuffer.data(), static_cast<int>(_tempBuffer.size()), 0);
	if (recvLen > 0)
	{
		_recvBuffer.insert(
			_recvBuffer.end(),
			_tempBuffer.data(),
			_tempBuffer.data() + recvLen
		);
	}
	
	return recvLen;
}
