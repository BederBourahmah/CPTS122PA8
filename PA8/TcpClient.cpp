#include "TcpClient.h"
#include <iostream>

TcpClient::TcpClient(std::string addr, unsigned short prt)
{
	address = addr;
	port = prt;
	socket = new sf::TcpSocket;
	socket->setBlocking(false);
	isConnected = false;
	socketStatus = socket->connect(address, port);
	enqueueEnemies(0);
}

TcpClient::~TcpClient()
{
	delete socket;
	socket = nullptr;
}

bool TcpClient::getIsConnected()
{
	return isConnected;
}

void TcpClient::enqueueEnemies(sf::Uint16 numberOfEnemiesToSend)
{
	sf::Packet packet;
	packet << numberOfEnemiesToSend;
	packetQueue.push(packet);
	std::cout << "Enqueued " << numberOfEnemiesToSend << " enemies." << std::endl;
}

void TcpClient::sendFrontOfQueue()
{
	if (socketStatus == sf::Socket::Disconnected)
	{
		socketStatus = socket->connect(address, port);
		return;
	}

	if (packetQueue.empty()) return;

	sf::Packet packet;
	packet = packetQueue.front();
	socketStatus = socket->send(packet);

	sf::Uint16 enemiesSent = 0;

	switch (socketStatus)
	{
	case sf::Socket::Done:
		
		packet >> enemiesSent;
		std::cout << "Sent " << enemiesSent << " enemies." << std::endl;
		packetQueue.pop();
		isConnected = true;
		return;
	case sf::Socket::Disconnected:
		socketStatus = socket->connect(address, port);
		return;
	case sf::Socket::Error:
		std::cout << "Error sending to server." << std::endl;
		return;
	case sf::Socket::NotReady:
	case sf::Socket::Partial:
	default:
		return;
	}
}

sf::Uint16 TcpClient::getEnemiesFromOpponent()
{
	if (socketStatus == sf::Socket::Status::Disconnected)
	{
		socketStatus = socket->connect(address, port);
		return 0;
	}

	sf::Packet packet;
	socketStatus = socket->receive(packet);

	sf::Uint16 numberOfEnemies = 0;

	switch (socketStatus)
	{
	case sf::Socket::Disconnected:
		socketStatus = socket->connect(address, port);
		return 0;
	case sf::Socket::Done:
		if (packet >> numberOfEnemies)
		{
			std::cout << "Received " << numberOfEnemies << " enemies." << std::endl;
			return numberOfEnemies;
		}

		std::cout << "Failed to read packet." << std::endl;
		return 0;
	case sf::Socket::NotReady:
	case sf::Socket::Partial:
	case sf::Socket::Error:
	default:
		return 0;
	}
}
