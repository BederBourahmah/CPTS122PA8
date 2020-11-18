#include "TcpServer.h"
#include <iostream>

TcpServer::TcpServer(unsigned short port)
{
	listener = new sf::TcpListener;
	listenerStatus = listener->listen(port);
	if (listenerStatus != sf::Socket::Done)
	{
		std::cout << "Failed to open TCP listener on port " << port << std::endl;
	}

	listener->setBlocking(false);
	listenerStatus = sf::Socket::NotReady;
	didConnect = false;
}

TcpServer::~TcpServer()
{
}

void TcpServer::attemptToConnect()
{
	listenerStatus = sf::Socket::NotReady;
	listenerStatus = listener->accept(client);

	didConnect = listenerStatus == sf::Socket::Done;
}

bool TcpServer::getDidConnect()
{
	return didConnect;
}
