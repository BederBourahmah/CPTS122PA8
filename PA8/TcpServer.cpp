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

	listenerStatus = listener->accept(client);
	if (listenerStatus != sf::Socket::Done)
	{
		std::cout << "Failed to accept TCP client on port " << port << std::endl;
	}
}

TcpServer::~TcpServer()
{
}
