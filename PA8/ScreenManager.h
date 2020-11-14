#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "MainMenu.h"
#include "SideScroller.h"
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "Screens.h"

class ScreenManager
{
public:
	ScreenManager(sf::VideoMode videoMode);
	~ScreenManager();
	Screen* getCurrentScreen();
private:
	MainMenu* mainMenu;
	SideScroller* sideScroller;
	Screens currentScreen;
};

#endif // !SCREEN_MANAGER_H
