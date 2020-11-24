#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "MainMenu.h"
#include "SideScroller.h"
#include "SwarmDefense.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Screen.h"
#include "Screens.h"
#include "TcpClient.h"
#include "TcpServer.h"
#include "LoadingModal.h"

class ScreenManager
{
public:
	ScreenManager(sf::VideoMode vm);
	~ScreenManager();
	Screen* getCurrentScreen();
	void updateState();
	bool shouldExitGame();
	void handleConnectToNetwork(std::string addr, unsigned int port, bool isServer);
	void drawTo(sf::RenderWindow& window);
	sf::Uint16 getEnemiesFromOpponent();
	void sendEnemiesToOpponent(sf::Uint16 enemiesToSend);

private:
	MainMenu* mainMenu;
	SideScroller* sideScroller;
	SwarmDefense* swarmDefense;
	Screens currentScreen;
	void initializeSelectedScreen(Screens selectedScreen);
	void processScreenSelection(MainMenu* currentScreenPtr);
	void deleteAllScreens();
	void switchToSelectedScreen(Screens selectedScreen);
	sf::VideoMode videoMode;
	TcpServer* server;
	TcpClient* client;
	LoadingModal* loadingModal;
	bool isAttemptingToConnect;
	void attemptConnection();
	bool isMultiplayer();
};

#endif // !SCREEN_MANAGER_H
