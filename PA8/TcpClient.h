#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <SFML/Network.hpp>
#include <iostream>
#include <queue>

class TcpClient
{
public:
	TcpClient(std::string addr, unsigned short prt);
	~TcpClient();

	bool getIsConnected();
	void enqueueEnemies(sf::Uint16 numberOfEnemiesToSend);
	void sendFrontOfQueue();
	sf::Uint16 getEnemiesFromOpponent();

private:
	sf::TcpSocket* socket;
	sf::Socket::Status socketStatus;
	sf::Socket::Status senderStatus;
	bool isConnected;
	std::string address;
	unsigned short port;
	std::queue<sf::Packet> packetQueue;
};

#endif // !TCP_CLIENT_H
