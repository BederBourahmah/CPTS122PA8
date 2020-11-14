#ifndef MOVEABLE_COMPONENT_H
#define MOVEABLE_COMPONENT_H

#include <SFML/Graphics.hpp>

class MoveableComponent
{
public:
	void centerHorizontal(sf::VideoMode const videoMode)
	{
		centerPosX = videoMode.width / 2;
		updatePosition();
	}

	void snapToVertical(sf::VideoMode const videoMode, int sections, int sectionToSnapTo)
	{
		float sizePerSection = (float)videoMode.height / (float)sections;
		float bottomOfSelectedSection = sectionToSnapTo * sizePerSection;
		float topOfSelectedSection = (sectionToSnapTo - 1) * sizePerSection;
		float centerOfSelectedSection = (bottomOfSelectedSection + topOfSelectedSection) / 2;
		centerPosY = centerOfSelectedSection;
		updatePosition();
	}

	void moveTo(float x, float y)
	{
		centerPosX = x;
		centerPosY = y;
		updatePosition();
	}

protected:

	virtual void updatePosition()=0;

	float getTopPosYToCenter()
	{
		return centerPosY - (totalHeight / 2);
	}

	float getLeftPosXToCenter()
	{
		return centerPosX - (totalWidth / 2);
	}

	float getBottomPosYToCenter()
	{
		return centerPosY + (totalHeight / 2);
	}

	float getRightPosXToCenter()
	{
		return centerPosX + (totalWidth / 2);
	}

	float centerPosX;
	float centerPosY;
	float totalWidth;
	float totalHeight;
};

#endif // !MOVEABLE_COMPONENT_H
