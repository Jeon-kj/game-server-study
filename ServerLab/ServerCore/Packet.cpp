#include "Packet.h"
#include "pch.h"

std::vector<char> MakePacket(const std::vector<char>& data, uint16 type)
{
	std::vector<char> packet;
	packet.reserve(100);

	uint16 packetLen = data.size() + 4;

	packet.push_back(static_cast<char>((packetLen >> 8) & 0xFF));
	packet.push_back(static_cast<char>(packetLen & 0xFF));

	packet.push_back(static_cast<char>((type >> 8) & 0xFF));
	packet.push_back(static_cast<char>(type & 0xFF));

	packet.insert(packet.end(), data.begin(), data.end());

	return packet;
}

ParseResult TryParsePacket(std::vector<char>& data, Session& session)
{
	const vector<char>& recvBuffer = session.GetRecvBuffer();

	if (recvBuffer.size() < 2)
		return ParseResult::NeedMore;

	uint16 packLen = (static_cast<uint16>(recvBuffer[0]) << 8) | static_cast<uint16>(recvBuffer[1]);

	if (packLen < 4)
		return ParseResult::Invalid;

	uint16 type = (static_cast<uint8>(recvBuffer[2]) << 8) & 0xFF00;
	type += static_cast<uint16>(recvBuffer[3]);

	if (type > static_cast<int32>(Type::Count)-1)
		return ParseResult::Invalid;

	if (recvBuffer.size() < packLen)
		return ParseResult::NeedMore;

	data.insert(data.begin(), recvBuffer.begin() + 4, recvBuffer.begin() + packLen);

	session.ConsumeRecvBuffer(packLen);	

	return ParseResult::Complete;
}
