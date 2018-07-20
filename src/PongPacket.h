#include <string>
#include "Vector2.h"
#pragma once

class PongPacket
{
public:

	// Packet Type
	enum PacketType
	{
		PACKET_INIT_MATCH,
		PACKET_PLAYER_1_POSITION,
		PACKET_PLAYER_2_POSITION,
		PACKET_BALL_POSITION
	};

	// Constructors
	PongPacket();
	PongPacket(PacketType type, Vector2 pos);
	~PongPacket();

	// Packet data
	PacketType packetType;
	Vector2 position;
	Vector2 direction;

	std::string data;
};

