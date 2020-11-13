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
	void draw(sf::RenderWindow &window);
	void moveSelectorDown();
	void moveSelectorUp();
private:
	TextComponent* start;
	TextComponent* exit;
	MenuSelector* selector;
	CurrentSelection currentSelection;
	void updateSelectorPosition();
};

#endif // !MAIN_MENU_H