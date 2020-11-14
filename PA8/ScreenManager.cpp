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
		if (currentScreenPtr->shouldExitGame())
		{
			switchToSelectedScreen(Screens::MainMenu);
		}
		return;
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

void ScreenManager::initializeSelectedScreen(Screens selectedScreen)
{
	switch (selectedScreen)
	{
	case Screens::MainMenu:
		mainMenu = new MainMenu(videoMode);
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
	delete sideScroller;
	sideScroller = nullptr;
}

void ScreenManager::switchToSelectedScreen(Screens selectedScreen)
{
	deleteAllScreens();
	initializeSelectedScreen(selectedScreen);
	currentScreen = selectedScreen;
}
