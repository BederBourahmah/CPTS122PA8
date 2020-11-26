#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <SFML/Network.hpp>
#include <queue>

/// <summary>
/// Container class for managing the SFML TCP server implementation.
/// </summary>
class TcpServer
{
public:
	/// <summary>
	/// Initializes the port which this server will listen to for incoming client connections.
	/// </summary>
	/// <param name="port">The port this server will listen to for incoming client connections.</param>
	TcpServer(unsigned short port);

	~TcpServer();

	/// <summary>
	/// Attempts to connect to a TCP client, setting the internal client socket to the newly connected client.
	/// </summary>
	void attemptToConnect();

	/// <summary>
	/// Gets the value of the private boolean flag that is set to true when a successfull connection is established with a client.
	/// </summary>
	/// <returns></returns>
	bool getDidConnect();

	/// <summary>
	/// Adds the provided number of enemies to the message queue.
	/// </summary>
	/// <param name="numberOfEnemiesToSend">The number of enemies that will be added to the message queue.</param>
	void enqueueEnemies(sf::Uint16 numberOfEnemiesToSend);

	/// <summary>
	/// Sends the front of the message queue to the client.
	/// </summary>
	void sendFrontOfQueue();

	/// <summary>
	/// Receives a message from the client containing the number of enemies that were sent to this server.
	/// </summary>
	/// <returns>The number of enemies that were sent to this server.</returns>
	sf::Uint16 getEnemiesFromOpponent();

private:
	/// <summary>
	/// A pointer to the listener used to establish a new connection to the client.
	/// </summary>
	sf::TcpListener* listener;

	/// <summary>
	/// A pointer to the socket used to connect to the client.
	/// </summary>
	sf::TcpSocket client;

	/// <summary>
	/// The status of the socket connected to the client.
	/// </summary>
	sf::Socket::Status socketStatus;

	/// <summary>
	/// Is set to true when a successfull connection to the server is established.
	/// </summary>
	bool didConnect;

	/// <summary>
	/// The queue containing the messages (packets) to send to the server.
	/// </summary>
	std::queue<sf::Packet> packetQueue;
};

#endif // !TCP_SERVER_H
