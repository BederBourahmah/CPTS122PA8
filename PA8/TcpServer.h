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
	void sendEnemiesToOpponent(sf::Uint16 numberOfEnemiesToSend);
	sf::Uint16 getEnemiesFromOpponent();

private:
	sf::TcpListener* listener;
	sf::TcpSocket client;
	bool didConnect;
};

#endif // !TCP_SERVER_H
