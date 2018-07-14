#include <SDL_net.h>
#include <iostream>
#include <string>
#pragma once

class NetworkManager
{
public:

	// Network State
	enum NetworkState
	{
		NETWORK_STATE_NULL,
		NETWORK_STATE_INITIALIZING,
		NETWORK_STATE_PAIRING_SENDING,
		NETWORK_STATE_PAIRING_RECEIVING,
		NETWORK_STATE_SENDING,
		NETWORK_STATE_RECEIVING
	};

	// NetWork Mode
	enum NetworkRole
	{
		NETWORK_SERVER,
		NETWORK_CLIENT
	};

	// Constructors

	NetworkManager();
	NetworkManager(NetworkRole mode);
	~NetworkManager();

	// Attributes

	NetworkState state;

	NetworkRole mode;

		// Read
	TCPsocket serverSocket;
	Uint16 serverPort;
	std::string serverIP;

		// Write
	TCPsocket clientSocket;
	Uint16 clientPort;
	std::string clientIP;

	// Methods
	void init();
	void update();

	// Config
	void readConfigFile();

	// Socket init
	bool openServerSocket();
	bool openClientSocket();

	//  Communication
	bool sendPairPacket();
	bool recvPairPacket();
};

