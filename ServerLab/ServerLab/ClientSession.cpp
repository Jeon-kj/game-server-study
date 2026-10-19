#include "pch.h"
#include "ClientSession.h"

void HandleClient(Session& session)
{
	while (true)
	{
		//recv
		int32 recvLen = session.Recv();
		if (recvLen == SOCKET_ERROR)
		{
			int32 errorCode = ::WSAGetLastError();
			cout << "Receive Error: " << errorCode << endl;
			return;
		}
		else if (recvLen == 0)
		{
			cout << "Client Disconnected" << endl;
			return;
		}

		std::vector<char> data;
		if (TryParsePacket(data, session) == ParseResult::Complete)
		{
			cout << "Receive Message : ";
			cout.write(data.data(), static_cast<std::streamsize>(data.size()));
			cout << endl;
		}
	}
}
