#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "MainMenu.h"
#include "HowToPlayMenu.h"
#include "SwarmDefense.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Screen.h"
#include "Screens.h"
#include "TcpClient.h"
#include "TcpServer.h"
#include "LoadingModal.h"

/// <summary>
/// This class manages the various screens and is the second layer below the main function.
/// </summary>
class ScreenManager
{
public:
	/// <summary>
	/// Initializes the video mode that will render the various screens.
	/// </summary>
	/// <param name="vm"></param>
	ScreenManager(sf::VideoMode vm);

	~ScreenManager();

	/// <summary>
	/// Returns the currently rendered screen.
	/// </summary>
	/// <returns>A pointer to the currently rendered screen.</returns>
	Screen* getCurrentScreen();

	/// <summary>
	/// Updates the internal state of the screen manager and underlying components as necessary.
	/// </summary>
	void updateState();

	/// <summary>
	/// Returns true if the player is ready to exit the game.
	/// </summary>
	/// <returns>True if the player is ready to exit the game.</returns>
	bool shouldExitGame();

	/// <summary>
	/// Connects to another player on the network.
	/// </summary>
	/// <param name="addr">The address of the other player. Only used if the other player is the server.</param>
	/// <param name="port">The port on this computer to listen to if this computer is ther server or of the other player if they are the server.</param>
	/// <param name="isServer">Whether this player is the server.</param>
	void handleConnectToNetwork(std::string addr, unsigned int port, bool isServer);

	/// <summary>
	/// Draws this component to the window.
	/// </summary>
	/// <param name="window">The window to draw to.</param>
	void drawTo(sf::RenderWindow& window);

	/// <summary>
	/// Gets the enemies sent by the other player.
	/// </summary>
	/// <returns>The number enemies sent by the other player.</returns>
	sf::Uint16 getEnemiesFromOpponent();

	/// <summary>
	/// Sends enemies to the other player.
	/// </summary>
	/// <param name="enemiesToSend">The number of enemies to send to the other player.</param>
	void sendEnemiesToOpponent(sf::Uint16 enemiesToSend);

private:
	/// <summary>
	/// The main menu screen.
	/// </summary>
	MainMenu* mainMenu;

	/// <summary>
	/// The sware defense screen.
	/// </summary>
	HowToPlayMenu* howToPlayMenu;
	SwarmDefense* swarmDefense;

	/// <summary>
	/// An enum representing the currently selected screen.
	/// </summary>
	Screens currentScreen;

	/// <summary>
	/// Initializes the currently selected screen, replacing the nullptr of that screen with a valid pointer to an object representing that screen.
	/// </summary>
	/// <param name="selectedScreen">The currently selected screen.</param>
	void initializeSelectedScreen(Screens selectedScreen);

	/// <summary>
	/// Processes the screen selection from the MainMenu screen.
	/// </summary>
	/// <param name="currentScreenPtr">The main menu screen.</param>
	void processScreenSelection(MainMenu* currentScreenPtr);

	/// <summary>
	/// Deletes all screens.
	/// </summary>
	void deleteAllScreens();

	/// <summary>
	/// Switches to the currently selected screen.
	/// </summary>
	/// <param name="selectedScreen">The currently selected screen.</param>
	void switchToSelectedScreen(Screens selectedScreen);

	/// <summary>
	/// The video mode that will render the underlying screens.
	/// </summary>
	sf::VideoMode videoMode;

	/// <summary>
	/// The SFML server implementation.
	/// </summary>
	TcpServer* server;
	
	/// <summary>
	/// The SFML client implementation.
	/// </summary>
	TcpClient* client;

	/// <summary>
	/// A loading modal the overlays the screen when it is in loading mode.
	/// </summary>
	LoadingModal* loadingModal;

	/// <summary>
	/// Is true when the game is trying to connect to another player on the network.
	/// </summary>
	bool isAttemptingToConnect;

	/// <summary>
	/// Attempt to connect to another player on the network.
	/// </summary>
	void attemptConnection();
	
	/// <summary>
	/// Returns true if the player selected multiplayer mode.
	/// </summary>
	/// <returns></returns>
	bool isMultiplayer();
};

#endif // !SCREEN_MANAGER_H
