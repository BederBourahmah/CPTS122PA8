#ifndef HOW_TO_PLAY_MENU_H
#define HOW_TO_PLAY_MENU_H

#include <iostream>
#include "TextComponent.h"
#include "MenuSelector.h"
#include <SFML/Graphics.hpp>
#include "Screen.h"

class HowToPlayMenu : public Screen
{
private:
	TextComponent* rulesTextHeader;
	TextComponent* rulesTextBody;
	MenuSelector* selector;
	TextComponent* returnText;
	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;
	void handleKeyPressEvent(sf::Event event);
	sf::VideoMode videoMode;
	bool shouldGoBackToMainMenu;
	bool loadRulesMenuBackgroundTexture();
	bool loadRulesMenuBackgroundSprite(sf::VideoMode const videoMode);

public:	
	HowToPlayMenu(sf::VideoMode const vm, sf::RenderWindow& window);
	~HowToPlayMenu();
	void drawTo(sf::RenderWindow& window);
	void processKeyboardInput();
	void processMousePosition(sf::Vector2i mouseWindowPosition);
	void processMouseClick();
	bool shouldExitGame();
	void handleEvents(sf::RenderWindow& window);
	void updateState();
};


#endif