#include "TcpClient.h"

TcpClient::TcpClient(std::string address, unsigned short port)
{
	socket = new sf::TcpSocket;
	socketStatus = socket->connect(address, port);
}

TcpClient::~TcpClient()
{
	delete socket;
	socket = nullptr;
}
