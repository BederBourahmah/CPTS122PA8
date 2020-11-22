#ifndef MOVEABLE_RECTANGLE_H
#define MOVEABLE_RECTANGLE_H

#include "MoveableComponent.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class MoveableRectangle : public MoveableComponent
{
public:
	MoveableRectangle(sf::Vector2f dimensions, sf::Color color);
	MoveableRectangle(sf::Vector2f dimensions, sf::Color color, short int newId);
	MoveableRectangle(sf::Vector2f dimensions, std::string asset);
	void drawTo(sf::RenderWindow& window);

	bool didCollideWithOtherComponent(MoveableRectangle otherComponent);

	int getId();

private:
	sf::RectangleShape shape;
	void updatePosition();

	static bool didComponentsCollide(MoveableRectangle componentA, MoveableRectangle componentB)
	{
		return doOverlapOnX(componentA, componentB) && doOverlapOnY(componentA, componentB);
	}

	static bool doOverlapOnX(MoveableRectangle componentA, MoveableRectangle componentB)
	{
		return componentA.getRightPosXToCenter() >= componentB.getLeftPosXToCenter() && componentA.getLeftPosXToCenter() <= componentB.getRightPosXToCenter();
	}

	static bool doOverlapOnY(MoveableRectangle componentA, MoveableRectangle componentB)
	{
		return componentA.getBottomPosYToCenter() >= componentB.getTopPosYToCenter() && componentA.getTopPosYToCenter() <= componentB.getBottomPosYToCenter();
	}

	int id;

	sf::Texture texture;
};

#endif // !MOVEABLE_RECTANGLE_H
