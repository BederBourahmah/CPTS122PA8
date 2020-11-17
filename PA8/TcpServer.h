#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <SFML/Network.hpp>

class TcpServer
{
public:
	TcpServer(unsigned short port);
	~TcpServer();

private:
	sf::TcpListener* listener;
	sf::Socket::Status listenerStatus;
	sf::TcpSocket client;
};

#endif // !TCP_SERVER_H
