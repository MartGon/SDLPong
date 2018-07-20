#include "NetworkManager.h"
#include <fstream>
#include <sstream>

// Constructors

NetworkManager::NetworkManager()
{

}

NetworkManager::NetworkManager(NetworkManager::NetworkRole mode)
{
	init();
	readConfigFile();
	this->mode = mode;
	state = NETWORK_STATE_INITIALIZING;
}

NetworkManager::~NetworkManager()
{
}

// Methods

void NetworkManager::init()
{
	if (SDLNet_Init() == -1) 
	{
		std::cout << "SDLNet_Init: " << SDLNet_GetError() << "\n";
		return;
	}
}

void NetworkManager::readConfigFile()
{
	// Open File
	std::string configFileName = "network-config.txt";
	std::ifstream configFile(configFileName);
	
	if (!configFile)
	{
		std::cout << "Couldn't open " << configFileName << "\n";
		return;
	}

	// Line for reading
	std::string line;

	// Read Server IP
	std::getline(configFile, serverIP);
	std::cout << "Read IP " << serverIP << "\n";

	// Read Server Port
	std::getline(configFile, line);
	serverPort = std::stoi(line);
	std::cout << "Read port " << serverPort << "\n";

	// Read client IP
	std::getline(configFile, clientIP);
	std::cout << "Write IP " << clientIP << "\n";

	// Read server IP
	std::getline(configFile, line);
	clientPort = std::stoi(line);
	std::cout << "Write Port " << clientPort << "\n";
}

bool NetworkManager::openServerSocket()
{
	IPaddress ip;

	if (SDLNet_ResolveHost(&ip, NULL, serverPort) == -1)
	{
		std::cout << "SDLNet_ResolveHost: " << SDLNet_GetError() << "\n";
		return false;
	}

	serverSocket = SDLNet_TCP_Open(&ip);
	if (!serverSocket)
	{
		std::cout << "SDLNet_TCP_Open: " << SDLNet_GetError() << "\n";
		return false;
	}

	std::cout << "TCP Read Port " << serverPort << " Opened Successfully! \n";
	return true;
}

bool NetworkManager::openClientSocket()
{
	IPaddress ip;

	if (SDLNet_ResolveHost(&ip, clientIP.c_str(), clientPort) == -1)
	{
		std::cout << "SDLNet_ResolveHost: " << SDLNet_GetError() << "\n";
		return false;
	}

	clientSocket = SDLNet_TCP_Open(&ip);
	if (!clientSocket)
	{
		std::cout << "SDLNet_TCP_Open: " << SDLNet_GetError() << "\n";
		return false;
	}

	std::cout << "TCP Write Port " << clientPort << " Opened Successfully! \n";
	return true;
}

bool NetworkManager::sendPairPacket()
{
	if (!clientSocket)
	{
		std::cout << "Can't send packet, write socket is not opened \n";
		return false;
	}

	std::string data = "Hello!\n";

	int len;
	int result;

	len = data.length() + 1;
	result = SDLNet_TCP_Send(clientSocket, data.c_str(), len);

	if (result < len)
	{
		std::cout << "SDLNet_TCP_Send: " << SDLNet_GetError() << "\n";
		return false;
	}

	std::cout << "Pair packet sent succesfully \n";
	return true;
}

bool NetworkManager::recvPairPacket()
{
	if (mode == NETWORK_SERVER)
	{
		if (!serverSocket)
		{
			std::cout << "Can't send packet, read socket is not opened \n";
			return false;
		}
	}

	int result;
	char msg[1024];

	if (clientSocket)
	{
		result = SDLNet_TCP_Recv(clientSocket, msg, 1024);

		if (result <= 0)
		{
			std::cout << "SDLNet_TCP_Recv: " << SDLNet_GetError() << "\n";
			return false;
		}

		std::cout << "Pair packet: " << msg << " recv succesfully \n";
		return true;
	}
	else
	{
		clientSocket = SDLNet_TCP_Accept(serverSocket);
		std::cout << " Connection accepted succesfully \n";
		return false;
	}
}

void NetworkManager::update()
{
	if (mode == NETWORK_SERVER)
	{
		switch (state)
		{
		case NETWORK_STATE_INITIALIZING:
			if (openServerSocket())
				state = NETWORK_STATE_PAIRING_RECEIVING;
			break;
		case NETWORK_STATE_PAIRING_RECEIVING:
			if (recvPairPacket())
				state = NETWORK_STATE_PAIRING_SENDING;
			break;
		case NETWORK_STATE_PAIRING_SENDING:
			if (sendPairPacket())
				state = NETWORK_STATE_PAIRING_RECEIVING;
			break;
		default:
			break;
		}
	}
	else if(mode == NETWORK_CLIENT)
	{
		switch (state)
		{
		case NETWORK_STATE_INITIALIZING:
			if (openClientSocket())
				state = NETWORK_STATE_PAIRING_SENDING;
			break;
		case NETWORK_STATE_PAIRING_SENDING:
			if (sendPairPacket())
				state = NETWORK_STATE_PAIRING_RECEIVING;
			break;
		case NETWORK_STATE_PAIRING_RECEIVING:
			if (recvPairPacket())
				state = NETWORK_STATE_PAIRING_SENDING;
			break;
		default:
			break;
		}
	}
}