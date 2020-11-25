#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <SFML/Network.hpp>
#include <iostream>
#include <queue>

/// <summary>
/// Container class for managing the SFML TCP client implementation.
/// </summary>
class TcpClient
{
public:
	/// <summary>
	/// This initializes the address and port of the server.
	/// </summary>
	/// <param name="addr">The IP address of the server.</param>
	/// <param name="prt">The port of the server.</param>
	TcpClient(std::string addr, unsigned short prt);

	~TcpClient();

	/// <summary>
	/// Returns the value of the private boolean flag that is set to true when a successfull connection to the server is established. 
	/// </summary>
	/// <returns>True if a successfull connection to the server has been established.</returns>
	bool getIsConnected();

	/// <summary>
	/// Adds the provided number of enemies to the message queue.
	/// </summary>
	/// <param name="numberOfEnemiesToSend">The number of enemies that will be added to the message queue.</param>
	void enqueueEnemies(sf::Uint16 numberOfEnemiesToSend);

	/// <summary>
	/// Sends the front of the message queue to the server.
	/// </summary>
	void sendFrontOfQueue();

	/// <summary>
	/// Receives a message from the server containing the number of enemies that were sent to this client.
	/// </summary>
	/// <returns>The number of enemies that were sent to this client.</returns>
	sf::Uint16 getEnemiesFromOpponent();

private:
	/// <summary>
	/// A pointer to the socket used to connect to the server.
	/// </summary>
	sf::TcpSocket* socket;

	/// <summary>
	/// The status of the socket connected to the server.
	/// </summary>
	sf::Socket::Status socketStatus;

	/// <summary>
	/// Is set to true when a successfull connection to the server is established.
	/// </summary>
	bool isConnected;

	/// <summary>
	/// The IP address of the server.
	/// </summary>
	std::string address;

	/// <summary>
	/// The port of the server.
	/// </summary>
	unsigned short port;

	/// <summary>
	/// The queue containing the messages (packets) to send to the server.
	/// </summary>
	std::queue<sf::Packet> packetQueue;
};

#endif // !TCP_CLIENT_H
