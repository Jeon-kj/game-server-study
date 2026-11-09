#pragma once

enum
{
	S_TEST = 1
};

#pragma pack(1)
struct PKT_S_TEST
{
	struct BuffsListItem
	{
		uint64 buffId;
		float remainTime;
	};

	uint16 packetSize;	// 공용 헤더
	uint16 pakcetId;	// 공용 헤더
	uint64 id;	// 8
	uint32 hp;	// 4
	uint16 attack;	// 2
	uint16 buffsOffset;
	uint16 buffsCount;

	bool Validate()
	{
		uint32 size = 0;
		size += sizeof(PKT_S_TEST);
		size += buffsCount * sizeof(BuffsListItem);
		if (size != packetSize)
			return false;

		if (buffsOffset + buffsCount * sizeof(BuffsListItem) > packetSize)
			return false;

		return true;
	}
};
#pragma pack()

class ClientPacketHandler
{
public:
	static void HandlePacket(BYTE* buffer, int32 len);

	static void Handle_S_TEST(BYTE* buffer, int32 len);
};

