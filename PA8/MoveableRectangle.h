#ifndef MOVEABLE_RECTANGLE_H
#define MOVEABLE_RECTANGLE_H

#include "MoveableComponent.h"
#include <SFML/Graphics.hpp>

class MoveableRectangle : public MoveableComponent
{
public:
	MoveableRectangle(sf::Vector2f dimensions, sf::Color color);
	void drawTo(sf::RenderWindow& window);
private:
	sf::RectangleShape shape;
	void updatePosition();
};

#endif // !MOVEABLE_RECTANGLE_H
