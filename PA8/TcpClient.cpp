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
