#pragma once

#include "CorePch.h"

//Data Struct
//[len][len][type][type][data]

enum class ParseResult
{
	NeedMore,
	Invalid,
	Complete
};

enum class Type
{
	TextMessage,

	Count
};

//struct Packet
//{
//	uint16 type;
//	std::vector<char> data;
//};

std::vector<char> MakePacket(const std::vector<char>& data, uint16 type);
ParseResult TryParsePacket(std::vector<char>& data, Session& session);
