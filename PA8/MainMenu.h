#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "TextComponent.h"
#include "MenuSelector.h"
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "Screens.h"
#include "MainMenuSelection.h"
#include "IpAddressInputModal.h"
#include "TcpServer.h"

class MainMenu : public Screen
{
public:
	MainMenu(sf::VideoMode const);
	~MainMenu();
	void drawTo(sf::RenderWindow &window);
	void moveSelectorDown();
	void moveSelectorUp();
	void processKeyboardInput();
	void processMousePosition(sf::Vector2i mouseWindowPosition);
	void processMouseClick();
	bool shouldExitGame();
	Screens getSelectedScreen();
	void handleEvents(sf::RenderWindow& window);
	void updateState();
private:
	TextComponent* sideScrollerText;
	TextComponent* swarmDefenderText;
	TextComponent* exitText;
	MenuSelector* selector;
	MainMenuSelection currentSelection;
	Screens selectedScreen;
	void updateSelectorPosition();
	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;
	bool loadMainMenuBackgroundTexture();
	bool loadMainMenuBackgroundSprite(sf::VideoMode const videoMode);
	void handleKeyPressEvent(sf::Event event);
	IpAddressInputModal* modal;
	TcpServer* server;
};

#endif // !MAIN_MENU_H