#include "NetworkAgent.h"

// Attributes


// Constructors

NetworkAgent::NetworkAgent()
{
		std::cout << "Inicializando networking\n";
		initNetworking();
}

NetworkAgent::~NetworkAgent()
{
}

// Methods

void NetworkAgent::initNetworking()
{
	if (SDLNet_Init() == -1)
	{
		std::cout << "SDLNet_Init: " << SDLNet_GetError() << "\n";
		return;
	}

}

bool NetworkAgent::readConfigFile()
{
	std::cout << "Parent read mehtod\n";
	return false;
}

bool NetworkAgent::establishConnection()
{
	return false;
}

bool NetworkAgent::sendPacket(TCPsocket socket, PongPacket* packet)
{
	if (!socket)
	{
		std::cout << "Can't send packet, socket is not opened \n";
		return false;
	}

	int result;
	int len = sizeof(PongPacket);
	result = SDLNet_TCP_Send(socket, packet, len);

	if (result < len)
	{
		std::cout << "SDLNet_TCP_Send: " << SDLNet_GetError() << "\n";
		return false;
	}

	//std::cout << "Pair packet sent succesfully \n";
	return true;
}

PongPacket* NetworkAgent::recvPacket(TCPsocket socket)
{
	if (!socket)
	{
		std::cout << "Can't receive packet, socket is not opened \n";
		return nullptr;
	}

	PongPacket *packet = new PongPacket();
	int result;
	int len = sizeof(PongPacket);
	result = SDLNet_TCP_Recv(socket, packet, len);

	if (result <= 0)
	{
		std::cout << "SDLNet_TCP_Recv: " << SDLNet_GetError() << "\n";
		return nullptr;
	}

	//std::cout << "Pair packet: " << len << " recv succesfully \n";
	return packet;
}

bool NetworkAgent::sendPacket(PongPacket *packet)
{
	return false;
}

PongPacket* NetworkAgent::recvPacket()
{
	return nullptr;
}

void NetworkAgent::destroy()
{
	// Virtual hook
	beforeDestroy();

	// Reset flag
	printf("Destroying network agent\n");

	// Calling SDL
	SDLNet_Quit();

	// Destroying pointer
	this->~NetworkAgent();
}

void NetworkAgent::beforeDestroy()
{
	printf("Parent method\n");
}