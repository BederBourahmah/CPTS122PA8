#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <SFML/Network.hpp>
#include <queue>

class TcpServer
{
public:
	TcpServer(unsigned short port);
	~TcpServer();

	void attemptToConnect();
	bool getDidConnect();
	void enqueueEnemies(sf::Uint16 numberOfEnemiesToSend);
	void sendFrontOfQueue();
	sf::Uint16 getEnemiesFromOpponent();

private:
	sf::TcpListener* listener;
	sf::TcpSocket client;
	sf::Socket::Status socketStatus;
	bool didConnect;
	std::queue<sf::Packet> packetQueue;
};

#endif // !TCP_SERVER_H
