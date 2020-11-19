#ifndef MENU_SELECTOR_H
#define MENU_SELECTOR_H

#include <SFML/Graphics.hpp>
#include "GUIComponent.h"

class MenuSelector : public GUIComponent
{
public:
	MenuSelector(float width, float height);

	void updatePosition();
	void drawTo(sf::RenderWindow& window);

private:
	sf::RectangleShape topLeftBorder;
	sf::RectangleShape bottomLeftBorder;
	sf::RectangleShape topRightBorder;
	sf::RectangleShape bottomRightBorder;
};

#endif // !MENU_SELECTOR_H
