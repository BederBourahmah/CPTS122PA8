#ifndef MODAL_BORDER_H
#define MODAL_BORDER_H

#include "GUIComponent.h"
#include <SFML/Graphics.hpp>

class ModalBorder : public GUIComponent
{
public:
	ModalBorder(float width, float height);
	void updatePosition();
	void drawTo(sf::RenderWindow& window);

private:
	sf::RectangleShape topLeftBorder;
	sf::RectangleShape bottomLeftBorder;
	sf::RectangleShape topRightBorder;
	sf::RectangleShape bottomRightBorder;
	sf::RectangleShape topBorder;
	sf::RectangleShape bottomBorder;
	sf::RectangleShape leftBorder;
	sf::RectangleShape rightBorder;
};

#endif // !MODAL_BORDER_H
