#include "NetworkAgent.h"
#pragma once

class NetworkServer : public NetworkAgent
{
public:

	enum ServerState
	{
		SERVER_STATE_NULL,
		SERVER_READ_CONFIG_FILE,
		SERVER_STATE_OPENING_SOCKET,
		SERVER_STATE_PAIRING,
		SERVER_STATE_SENDING,
		SERVER_STATE_RECEIVING,
		SERVER_STATE_CONNECTION_ESTABLISHED
	};

	// Constructors
	NetworkServer();
	~NetworkServer();

	// Attributes

		// State
	ServerState state;

		// Server side
	TCPsocket serverSocket;
	Uint16 serverPort;

		// Client side
	TCPsocket clientSocket;

	// Methods
		// Uppper
	virtual bool readConfigFile();
	virtual bool establishConnection();

		// Own
	bool openServerSocket();
	bool pairWithClient();

		// Communication
	virtual bool sendPacket(PongPacket* packet);
	virtual PongPacket* recvPacket();

	// Other
	virtual void beforeDestroy();
};

