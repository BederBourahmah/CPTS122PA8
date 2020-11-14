#include "MoveableRectangle.h"

MoveableRectangle::MoveableRectangle(sf::Vector2f dimensions, sf::Color color)
{
	shape = sf::RectangleShape(dimensions);
	shape.setFillColor(color);
	centerPosX = dimensions.x / 2;
	centerPosY = dimensions.y / 2;
	shape.setOrigin(centerPosX, centerPosY);
	totalHeight = dimensions.y;
	totalWidth = dimensions.x;
}

void MoveableRectangle::drawTo(sf::RenderWindow& window)
{
	window.draw(shape);
}

void MoveableRectangle::updatePosition()
{
	shape.setPosition(centerPosX, centerPosY);
}
