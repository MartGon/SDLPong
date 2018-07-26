#include <string>
#include "Vector2.h"
#include "GameObject.h"
#pragma once

class PongPacket
{
public:

	// TODO - Needs Serialization

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
	Uint16 id = -1;
	Vector2 position;
	Vector2 direction;
	//std::string data;

	// New setup
	//GameObject gameObject;
};

