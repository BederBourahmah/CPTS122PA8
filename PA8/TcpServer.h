#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <SFML/Network.hpp>

class TcpServer
{
public:
	TcpServer(unsigned short port);
	~TcpServer();

	void attemptToConnect();
	bool getDidConnect();

private:
	sf::TcpListener* listener;
	sf::Socket::Status listenerStatus;
	sf::TcpSocket client;
	bool didConnect;
};

#endif // !TCP_SERVER_H
