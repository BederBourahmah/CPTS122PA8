#include "ScreenManager.h"

ScreenManager::ScreenManager(sf::VideoMode vm)
{
	videoMode = vm;
	mainMenu = new MainMenu(videoMode, this, &ScreenManager::handleConnectToNetwork);
	currentScreen = Screens::MainMenu;
	sideScroller = nullptr;
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
	case Screens::SideScroller:
		return sideScroller;
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
	currentScreenPtr->processMouseClick();
	currentScreenPtr->updateState();

	if (currentScreen == Screens::MainMenu)
	{
		processScreenSelection((MainMenu*)currentScreenPtr);
		return;
	}
	
	if (currentScreen == Screens::SideScroller)
	{
		if (currentScreenPtr->shouldExitGame())
		{
			switchToSelectedScreen(Screens::MainMenu);
		}
		return;
	}

	if (currentScreen == Screens::SwarmDefense)
	{
		if (currentScreenPtr->shouldExitGame())
		{
			switchToSelectedScreen(Screens::MainMenu);
			return;
		}
	}
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
		isAttemptingToConnect = true;
	}
	else {
		client = new TcpClient(addr, port);
	}
	loadingModal = new LoadingModal(videoMode);

}

void ScreenManager::drawTo(sf::RenderWindow& window)
{
	getCurrentScreen()->drawTo(window);

	if (loadingModal != nullptr) loadingModal->drawTo(window);
}

void ScreenManager::initializeSelectedScreen(Screens selectedScreen)
{
	switch (selectedScreen)
	{
	case Screens::MainMenu:
		mainMenu = new MainMenu(videoMode, this, &ScreenManager::handleConnectToNetwork);
		break;
	case Screens::SwarmDefense:
		swarmDefense = new SwarmDefense(videoMode);
		break;
	case Screens::SideScroller:
		sideScroller = new SideScroller(videoMode);
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
	delete sideScroller;
	sideScroller = nullptr;
}

void ScreenManager::switchToSelectedScreen(Screens selectedScreen)
{
	deleteAllScreens();
	initializeSelectedScreen(selectedScreen);
	currentScreen = selectedScreen;
}

void ScreenManager::attemptConnection()
{
	if (server == nullptr) return;

	server->attemptToConnect();
	if (server->getDidConnect())
	{
		isAttemptingToConnect = false;
		delete loadingModal;
		loadingModal = nullptr;
	}
}
