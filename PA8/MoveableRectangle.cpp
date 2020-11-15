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
	id = INT16_MIN;
}

MoveableRectangle::MoveableRectangle(sf::Vector2f dimensions, sf::Color color, short int newId)
{
	shape = sf::RectangleShape(dimensions);
	shape.setFillColor(color);
	centerPosX = dimensions.x / 2;
	centerPosY = dimensions.y / 2;
	shape.setOrigin(centerPosX, centerPosY);
	totalHeight = dimensions.y;
	totalWidth = dimensions.x;
	id = newId;
}

void MoveableRectangle::drawTo(sf::RenderWindow& window)
{
	window.draw(shape);
}

bool MoveableRectangle::didCollideWithOtherComponent(MoveableRectangle otherComponent)
{
	return didComponentsCollide(*this, otherComponent);
}

void MoveableRectangle::updatePosition()
{
	shape.setPosition(centerPosX, centerPosY);
}
