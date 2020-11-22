#include "MoveableRectangle.h"

MoveableRectangle::MoveableRectangle(sf::Vector2f dimensions)
{
	shape = sf::RectangleShape(dimensions);
	centerPosX = dimensions.x / 2;
	centerPosY = dimensions.y / 2;
	shape.setOrigin(centerPosX, centerPosY);
	totalHeight = dimensions.y;
	totalWidth = dimensions.x;
}

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

MoveableRectangle::MoveableRectangle(sf::Vector2f dimensions, const sf::Texture* txtr)
{
	shape = sf::RectangleShape(dimensions);
	
	shape.setTexture(txtr);
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

bool MoveableRectangle::didCollideWithOtherComponent(MoveableRectangle otherComponent)
{
	return didComponentsCollide(*this, otherComponent);
}

void MoveableRectangle::setTexture(const sf::Texture* newTexture)
{
	shape.setTexture(newTexture);
}

void MoveableRectangle::mirror()
{
	shape.setScale(-1.0f, 1.0f);
}

bool MoveableRectangle::isLeftOfCenter(float center)
{
	return centerPosX < center;
}

void MoveableRectangle::updatePosition()
{
	shape.setPosition(centerPosX, centerPosY);
}
