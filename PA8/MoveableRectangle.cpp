#include "MoveableRectangle.h"

MoveableRectangle::MoveableRectangle(sf::Vector2f dimensions)
{
	shape = sf::RectangleShape(dimensions);
	centerPosX = dimensions.x / 2.0f;
	centerPosY = dimensions.y / 2.0f;
	shape.setOrigin(centerPosX, centerPosY);
	totalHeight = dimensions.y;
	totalWidth = dimensions.x;
}

MoveableRectangle::MoveableRectangle(sf::Vector2f dimensions, sf::Color color)
{
	shape = sf::RectangleShape(dimensions);
	shape.setFillColor(color);
	centerPosX = dimensions.x / 2.0f;
	centerPosY = dimensions.y / 2.0f;
	shape.setOrigin(centerPosX, centerPosY);
	totalHeight = dimensions.y;
	totalWidth = dimensions.x;
}

MoveableRectangle::MoveableRectangle(sf::Vector2f dimensions, const sf::Texture* txtr)
{
	shape = sf::RectangleShape(dimensions);
	
	shape.setTexture(txtr);
	centerPosX = dimensions.x / 2.0f;
	centerPosY = dimensions.y / 2.0f;
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

void MoveableRectangle::updateDimensions(sf::Vector2f dimensions, sf::Vector2f originOffset)
{
	shape = sf::RectangleShape(dimensions);
	auto oldCenterX = centerPosX;
	centerPosX += (totalWidth - dimensions.x) / 2.0f;
	auto oldCenterY = centerPosY;
	centerPosY += (totalHeight - dimensions.y) / 2.0f;
	shape.setOrigin((dimensions.x + originOffset.x)/2.0f, (dimensions.y + originOffset.y)/2.0f);
	totalHeight = dimensions.y;
	totalWidth = dimensions.x;
	shape.setPosition(oldCenterX, oldCenterY);
}

void MoveableRectangle::updatePosition()
{
	shape.setPosition(centerPosX, centerPosY);
}
