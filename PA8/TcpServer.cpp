#include "TcpServer.h"
#include <iostream>

TcpServer::TcpServer(unsigned short port)
{
	didConnect = false;
	listener = new sf::TcpListener;
	if (listener->listen(port) != sf::Socket::Done)
	{
		//TODO: handle this case and have the user select another port
		std::cout << "Failed to open TCP listener on port " << port << std::endl;
		return;
	}

	listener->setBlocking(false);
	socketStatus = sf::Socket::Disconnected;
}

TcpServer::~TcpServer()
{
}

void TcpServer::attemptToConnect()
{
	if (socketStatus == sf::Socket::Disconnected)
	{
		socketStatus = listener->accept(client);
		return;
	}

	if (socketStatus == sf::Socket::Done)
	{
		auto remoteAddr = client.getRemoteAddress();
		didConnect = true;
		std::cout << "Connected successfully to " << remoteAddr.toString() << std::endl;
		client.setBlocking(false);
		enqueueEnemies(0);
		return;
	}

	socketStatus = sf::Socket::Disconnected;
}

bool TcpServer::getDidConnect()
{
	return didConnect;
}

void TcpServer::enqueueEnemies(sf::Uint16 numberOfEnemiesToSend)
{
	sf::Packet packet;
	packet << numberOfEnemiesToSend;
	packetQueue.push(packet);
	std::cout << "Enqueued " << numberOfEnemiesToSend << " enemies." << std::endl;
}

void TcpServer::sendFrontOfQueue()
{
	if (socketStatus == sf::Socket::Status::Disconnected)
	{
		std::cout << "Disconnected!" << std::endl;
		attemptToConnect();
		return;
	}

	if (packetQueue.empty()) return;

	sf::Packet packet;
	packet = packetQueue.front();
	socketStatus = client.send(packet);

	sf::Uint16 enemiesSent = 0;

	switch (socketStatus)
	{
	case sf::Socket::Done:
		packet >> enemiesSent;
		std::cout << "Sent " << enemiesSent << " enemies." << std::endl;
		packetQueue.pop();
		didConnect = true;
		return;
	case sf::Socket::Disconnected:
		std::cout << "Disconnected!" << std::endl;
		attemptToConnect();
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

sf::Uint16 TcpServer::getEnemiesFromOpponent()
{
	sf::Packet packet;
	if (client.receive(packet) != sf::Socket::Status::Done) return 0;

	sf::Uint16 numberOfEnemies = 0;
	if (packet >> numberOfEnemies)
	{
		std::cout << "Received " << numberOfEnemies << " enemies." << std::endl;
		return numberOfEnemies;
	}

	return 0;
}
