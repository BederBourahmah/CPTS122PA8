#include "TcpClient.h"

TcpClient::TcpClient(std::string addr, unsigned short prt)
{
	address = addr;
	port = prt;
	socket = new sf::TcpSocket;
	socket->setBlocking(false);
	didConnect = false;
	socket->connect(address, port);
}

TcpClient::~TcpClient()
{
	delete socket;
	socket = nullptr;
}

void TcpClient::checkConnection()
{
	didConnect = socket->getRemoteAddress() != sf::IpAddress::None;
}

bool TcpClient::getDidConnect()
{
	return didConnect;
}

void TcpClient::sendEnemiesToOpponent(sf::Uint16 numberOfEnemiesToSend)
{
	sf::Packet packet;
	packet << numberOfEnemiesToSend;
	socket->send(packet);
}

sf::Uint16 TcpClient::getEnemiesFromOpponent()
{
	sf::Packet packet;
	if (socket->receive(packet) != sf::Socket::Status::Done) return 0;

	sf::Uint16 numberOfEnemies = 0;
	if (packet >> numberOfEnemies) return numberOfEnemies;

	return 0;
}
