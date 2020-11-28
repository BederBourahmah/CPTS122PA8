#include "ScreenManager.h"

ScreenManager::ScreenManager(sf::VideoMode vm)
{
	videoMode = vm;
	mainMenu = new MainMenu(videoMode, this, &ScreenManager::handleConnectToNetwork);
	currentScreen = Screens::MainMenu;
	howToPlayMenu = new HowToPlayMenu(videoMode);
	swarmDefense = nullptr;
	server = nullptr;
	client = nullptr;
	loadingModal = nullptr;
	isAttemptingToConnect = false;
}

ScreenManager::~ScreenManager()
{
	deleteAllScreens();
	delete server;
	server = nullptr;
	delete client;
	client = nullptr;
	delete loadingModal;
	loadingModal = nullptr;
}

Screen* ScreenManager::getCurrentScreen()
{
	switch (currentScreen)
	{
	case Screens::MainMenu:
		return mainMenu;
	case Screens::HowToPlayMenu:
		return howToPlayMenu;
	case Screens::SwarmDefense:
		return swarmDefense;
	default:
		return nullptr;
	}
}

void ScreenManager::updateState()
{
	Screen* currentScreenPtr = getCurrentScreen();
	if (currentScreenPtr == nullptr) return;

	if (isAttemptingToConnect && loadingModal != nullptr)
	{
		loadingModal->updateState();
		attemptConnection();
		return;
	}

	currentScreenPtr->processKeyboardInput();
	currentScreenPtr->processMousePosition(sf::Mouse::getPosition());
	currentScreenPtr->updateState();

	if (currentScreen == Screens::MainMenu)
	{
		processScreenSelection((MainMenu*)currentScreenPtr);
		return;
	}
	
	if (currentScreen == Screens::HowToPlayMenu)
	{
		if (currentScreenPtr->shouldExitGame())
		{
			switchToSelectedScreen(Screens::MainMenu);
		}
		return;
	}

	if (currentScreen == Screens::SwarmDefense || currentScreen == Screens::HowToPlayMenu)
	{
		if (currentScreenPtr->shouldExitGame())
		{
			switchToSelectedScreen(Screens::MainMenu);
			return;
		}
	}

	if (client != nullptr) client->sendFrontOfQueue();

	if (server != nullptr) server->sendFrontOfQueue();
}

bool ScreenManager::shouldExitGame()
{
	if (currentScreen == Screens::Exit) return true;
	
	if (currentScreen == Screens::MainMenu)
	{
		return getCurrentScreen()->shouldExitGame();
	}

	return false;
}

void ScreenManager::handleConnectToNetwork(std::string addr, unsigned int port, bool isServer)
{
	if (isServer)
	{
		server = new TcpServer(port);
	}
	else {
		client = new TcpClient(addr, port);
	}

	isAttemptingToConnect = true;
	loadingModal = new LoadingModal(videoMode);
}

void ScreenManager::drawTo(sf::RenderWindow& window)
{
	getCurrentScreen()->drawTo(window);

	if (loadingModal != nullptr) loadingModal->drawTo(window);
}

sf::Uint16 ScreenManager::getEnemiesFromOpponent()
{
	if (server != nullptr) return server->getEnemiesFromOpponent();

	if (client != nullptr) return client->getEnemiesFromOpponent();

	return 0;
}

void ScreenManager::sendEnemiesToOpponent(sf::Uint16 enemiesToSend)
{
	if (server != nullptr) server->enqueueEnemies(enemiesToSend);

	if (client != nullptr) client->enqueueEnemies(enemiesToSend);
}

void ScreenManager::initializeSelectedScreen(Screens selectedScreen)
{
	switch (selectedScreen)
	{
	case Screens::MainMenu:
		mainMenu = new MainMenu(videoMode, this, &ScreenManager::handleConnectToNetwork);
		break;
	case Screens::SwarmDefense:
		swarmDefense = new SwarmDefense(videoMode, isMultiplayer(), this, &ScreenManager::sendEnemiesToOpponent, &ScreenManager::getEnemiesFromOpponent);
		break;
	case Screens::HowToPlayMenu: 
		return;
	case Screens::Exit:
		break;
	default:
		break;
	}
}

void ScreenManager::processScreenSelection(MainMenu* currentScreenPtr)
{
	Screens selectedScreen = (currentScreenPtr)->getSelectedScreen();
	if (currentScreen == selectedScreen) return;

	switchToSelectedScreen(selectedScreen);
}

void ScreenManager::deleteAllScreens()
{
	delete mainMenu;
	mainMenu = nullptr;
	delete swarmDefense;
	swarmDefense = nullptr;
	delete howToPlayMenu;
	howToPlayMenu = nullptr;
}

void ScreenManager::switchToSelectedScreen(Screens selectedScreen)
{
	//deleteAllScreens();
	initializeSelectedScreen(selectedScreen);
	currentScreen = selectedScreen;
}

void ScreenManager::attemptConnection()
{
	if (server != nullptr)
	{
		server->attemptToConnect();
		if (server->getDidConnect())
		{
			isAttemptingToConnect = false;
			delete loadingModal;
			loadingModal = nullptr;
			switchToSelectedScreen(Screens::SwarmDefense);
		}
		return;
	}

	if (client == nullptr) return;
	
	client->sendFrontOfQueue();
	if (client->getIsConnected())
	{
		isAttemptingToConnect = false;
		delete loadingModal;
		loadingModal = nullptr;
		switchToSelectedScreen(Screens::SwarmDefense);
	}
	
}

bool ScreenManager::isMultiplayer()
{
	return server != nullptr || client != nullptr;
}
