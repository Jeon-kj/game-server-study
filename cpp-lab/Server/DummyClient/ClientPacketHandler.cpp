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

	PKT_S_TEST* pkt = reinterpret_cast<PKT_S_TEST*>(buffer);

	if (pkt->Validate() == false)
		return;

	PKT_S_TEST::BuffsList buffs = pkt->GetBuffsList();

	cout << "bufCount : " << buffs.Count() << endl;
	for (int32 i = 0; i < buffs.Count(); i++)
		cout << "BufInfo : " << buffs[i].buffId << " " << buffs[i].remainTime << endl;

	for (auto it = buffs.begin(); it != buffs.end(); ++it)
		cout << "BufInfo : " << it->buffId << " " << it->remainTime << endl;

	for (auto& buff : buffs)
		cout << "BufInfo : " << buff.buffId << " " << buff.remainTime << endl;
}
