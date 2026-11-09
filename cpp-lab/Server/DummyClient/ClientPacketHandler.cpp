#include "pch.h"
#include "ClientPacketHandler.h"
#include "BufferReader.h"

void ClientPacketHandler::HandlePacket(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br >> header;

	switch (header.id)
	{
	case S_TEST:
		Handle_S_TEST(buffer, len);
		break;
	}
}

void ClientPacketHandler::Handle_S_TEST(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	if (len < sizeof(PKT_S_TEST))
		return;

	PKT_S_TEST pkt;
	br >> pkt;

	if (pkt.Validate() == false)
		return;

	vector<PKT_S_TEST::BuffsListItem> buffs;

	buffs.resize(pkt.buffsCount);
	for (int32 i = 0; i < pkt.buffsCount; i++)
		br >> buffs[i];

	cout << "BuffCount: " << pkt.buffsCount << endl;
	for (int32 i = 0; i < pkt.buffsCount; i++)
	{
		cout << "BuffInfo : " << buffs[i].buffId << " " << buffs[i].remainTime << endl;
	}
}
