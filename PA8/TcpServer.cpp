#include "TcpServer.h"
#include <iostream>

TcpServer::TcpServer(unsigned short port)
{
	listener = new sf::TcpListener;
	if (listener->listen(port) != sf::Socket::Done)
	{
		std::cout << "Failed to open TCP listener on port " << port << std::endl;
	}

	listener->setBlocking(false);
	didConnect = false;
}

TcpServer::~TcpServer()
{
}

void TcpServer::attemptToConnect()
{
	didConnect = listener->accept(client) == sf::Socket::Done;
}

bool TcpServer::getDidConnect()
{
	return didConnect;
}
