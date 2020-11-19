#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <SFML/Network.hpp>
#include <iostream>

class TcpClient
{
public:
	TcpClient(std::string addr, unsigned short prt);
	~TcpClient();

	void checkConnection();
	bool getDidConnect();
	void sendEnemiesToOpponent(sf::Uint16 numberOfEnemiesToSend);
	sf::Uint16 getEnemiesFromOpponent();

private:
	sf::TcpSocket* socket;
	sf::Socket::Status socketStatus;
	bool didConnect;
	std::string address;
	unsigned short port;
};

#endif // !TCP_CLIENT_H
