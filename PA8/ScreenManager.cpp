#include "ScreenManager.h"

ScreenManager::ScreenManager(sf::VideoMode videoMode)
{
	mainMenu = new MainMenu(videoMode);
	currentScreen = Screens::MainMenu;
	sideScroller = nullptr;
}

ScreenManager::~ScreenManager()
{
	delete mainMenu;
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
		break;
	}
}
