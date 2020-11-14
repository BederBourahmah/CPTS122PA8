#include "ScreenManager.h"

ScreenManager::ScreenManager(sf::VideoMode videoMode)
{
	mainMenu = new MainMenu(videoMode);
	currentScreen = Screens::MainMenu;
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
		break;
	default:
		break;
	}
}
