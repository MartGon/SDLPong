#include <SDL_net.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "PongPacket.h"
#pragma once
class NetworkAgent
{
public:
	// Constructors
	NetworkAgent();
	~NetworkAgent();

	// Methods
		// Initializing
	//static bool networkEnabled;
	static void initNetworking();

		// Configuration
	bool readingError = false;
	virtual bool readConfigFile();
	virtual bool establishConnection();

	// Communication
	virtual bool sendPacket(PongPacket* packet);
	virtual PongPacket* recvPacket();

	// Other
	void destroy();
	virtual void beforeDestroy();

protected:
		// Communication
	bool sendPacket(TCPsocket socket, PongPacket* packet);
	PongPacket* recvPacket(TCPsocket socket);
};

