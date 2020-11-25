#ifndef HOW_TO_PLAY_MENU_H
#define HOW_TO_PLAY_MENU_H

#include "TextComponent.h"
#include "MenuSelector.h"
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "Screens.h"
#include "MainMenuSelection.h"
#include "IpAddressInputModal.h"
#include "TcpServer.h"
#include "TcpClient.h"
#include "LoadingModal.h"
#include "SingleOrMultiplayerModal.h"

class HowToPlayMenu : public Screen
{
private:
	TextComponent* rulesTextHeader;
	TextComponent* rulesTextBody;
	MenuSelector* selector;
	TextComponent* returnText;
	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;
	Screens selectedScreen;
	MainMenuSelection currentSelection;
	void updateSelectorPosition();
	SingleOrMultiplayerModal* singVsMultiModal;
	void handleKeyPressEvent(sf::Event event);
	bool isAttemptingToConnect;
	sf::VideoMode videoMode;
	TcpServer* server;
	TcpClient* client;
	bool shouldGoBackToMainMenu;
	bool loadRulesMenuBackgroundTexture();
	bool loadRulesMenuBackgroundSprite(sf::VideoMode const videoMode);
	void handleClickEvent(sf::Event event);
	bool isMenuDisabled();

public:	
	HowToPlayMenu(sf::VideoMode const vm);
	~HowToPlayMenu();
	void drawTo(sf::RenderWindow& window);
	void processKeyboardInput();
	void processMousePosition(sf::Vector2i mouseWindowPosition);
	void processMouseClick();
	bool shouldExitGame();
	void handleEvents(sf::RenderWindow& window);
	void updateState();
	Screens getSelectedScreen();
	void moveSelectorDown();
	void moveSelectorUp();
};


#endif