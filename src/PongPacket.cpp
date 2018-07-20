#include "PongPacket.h"

// Constructors

PongPacket::PongPacket()
{
}

PongPacket::PongPacket(PongPacket::PacketType type, Vector2 pos)
{
	packetType = type;
	position = pos;
}

PongPacket::~PongPacket()
{
}
