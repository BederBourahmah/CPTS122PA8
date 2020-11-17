#include "TcpClient.h"

TcpClient::TcpClient(std::string address, unsigned short port)
{
	socket = new sf::TcpSocket;
	socketStatus = socket->connect(address, port, sf::seconds(10));
	if (socketStatus != sf::Socket::Status::Done)
	{
		std::cout << "Failed to connect to server." << std::endl;
	}
}

TcpClient::~TcpClient()
{
	delete socket;
	socket = nullptr;
}
