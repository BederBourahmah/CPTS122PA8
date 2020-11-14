#include "ScreenManager.h"

ScreenManager::ScreenManager(sf::VideoMode vm)
{
	videoMode = vm;
	mainMenu = new MainMenu(videoMode);
	currentScreen = Screens::MainMenu;
	sideScroller = nullptr;
}

ScreenManager::~ScreenManager()
{
	deleteAllScreens();
}

Screen* ScreenManager::getCurrentScreen()
{
	switch (currentScreen)
	{
	case Screens::MainMenu:
		return mainMenu;
	case Screens::SideScroller:
		return sideScroller;
	default:
		return nullptr;
	}
}

void ScreenManager::updateState()
{
	Screen* currentScreenPtr = getCurrentScreen();
	if (currentScreenPtr == nullptr) return;

	currentScreenPtr->processKeyboardInput();
	currentScreenPtr->processMousePosition(sf::Mouse::getPosition());
	currentScreenPtr->processMouseClick();

	if (currentScreen == Screens::MainMenu)
	{
		processScreenSelection((MainMenu*)currentScreenPtr);
		return;
	}

	if (currentScreen == Screens::SideScroller)
	{
		((SideScroller*)currentScreenPtr)->updateState();
		return;
	}
}

bool ScreenManager::shouldExitGame()
{
	if (currentScreen == Screens::Exit) return true;

	return getCurrentScreen()->shouldExitGame();
}

void ScreenManager::initializeSelectedScreen(Screens selectedScreen)
{
	switch (selectedScreen)
	{
	case Screens::MainMenu:
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
	Screens nextScreen = (currentScreenPtr)->getSelectedScreen();
	if (currentScreen == nextScreen) return;

	deleteAllScreens();
	initializeSelectedScreen(nextScreen);
	currentScreen = nextScreen;
}

void ScreenManager::deleteAllScreens()
{
	delete mainMenu;
	mainMenu = nullptr;
	delete sideScroller;
	sideScroller = nullptr;
}
