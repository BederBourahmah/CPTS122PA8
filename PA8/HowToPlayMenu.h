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
	sf::VideoMode videoMode;
	bool shouldGoBackToMainMenu;
	bool loadRulesMenuBackgroundTexture();
	bool loadRulesMenuBackgroundSprite(sf::VideoMode const videoMode);

public:	
	HowToPlayMenu(sf::VideoMode const vm);
	~HowToPlayMenu();
	void drawTo(sf::RenderWindow& window);
	void processKeyboardInput();
	void processMousePosition(sf::Vector2i mouseWindowPosition);
	void updateState();
	bool shouldExitGame();
	void handleEvents(sf::RenderWindow& window);

	/// <summary>
	/// Resets the internal state of this screen.
	/// </summary>
	void resetState();
};


#endif