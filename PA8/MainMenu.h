#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "TextComponent.h"
#include "MenuSelector.h"
#include <SFML/Graphics.hpp>

class MainMenu
{
public:
	MainMenu(sf::VideoMode const);
	~MainMenu();
	void draw(sf::RenderWindow &window);
private:
	TextComponent* Start;
	TextComponent* Exit;
	MenuSelector* Selector;
};

#endif // !MAIN_MENU_H