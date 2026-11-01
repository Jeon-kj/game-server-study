#include "pch.h"
#include "SendBuffer.h"

/*----------------
	SendBuffer
----------------*/

SendBuffer::SendBuffer(int32 bufferSize)
{
	_buffer.resize(bufferSize);
}

SendBuffer::~SendBuffer()
{
}

void SendBuffer::CopyData(void* data, int32 len)
{
	ASSERT_CRASH(len <= Capacity());
	::memcpy(_buffer.data(), data, len);
	_writeSize = len;
}
