#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "TextComponent.h"
#include "MenuSelector.h"
#include <SFML/Graphics.hpp>

enum class CurrentSelection
{
	Start,
	Exit
};

class MainMenu
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
private:
	TextComponent* start;
	TextComponent* exit;
	MenuSelector* selector;
	CurrentSelection currentSelection;
	void updateSelectorPosition();
	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;
	bool loadMainMenuBackgroundTexture();
	bool loadMainMenuBackgroundSprite(sf::VideoMode const videoMode);
	bool isExitingGame;
};

#endif // !MAIN_MENU_H