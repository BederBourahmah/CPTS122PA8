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
	void updateState();
	bool shouldExitGame();
private:
	MainMenu* mainMenu;
	SideScroller* sideScroller;
	Screens currentScreen;
	void initializeSelectedScreen(Screens selectedScreen);
	void processScreenSelection(MainMenu* currentScreenPtr);
	void deleteAllScreens();
};

#endif // !SCREEN_MANAGER_H
