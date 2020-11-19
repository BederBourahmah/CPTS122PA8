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

void TcpServer::sendEnemiesToOpponent(sf::Uint16 numberOfEnemiesToSend)
{
	sf::Packet packet;
	packet << numberOfEnemiesToSend;
	client.send(packet);
}

sf::Uint16 TcpServer::getEnemiesFromOpponent()
{
	sf::Packet packet;
	if (client.receive(packet) != sf::Socket::Status::Done) return 0;

	sf::Uint16 numberOfEnemies = 0;
	if (packet >> numberOfEnemies) return numberOfEnemies;

	return 0;
}
