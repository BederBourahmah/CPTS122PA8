#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <SFML/Network.hpp>

class TcpClient
{
public:
	TcpClient(std::string address, unsigned short port);
	~TcpClient();

private:
	sf::TcpSocket* socket;
	sf::Socket::Status socketStatus;
};

#endif // !TCP_CLIENT_H
