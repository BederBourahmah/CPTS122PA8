#ifndef MOVEABLE_COMPONENT_H
#define MOVEABLE_COMPONENT_H

#include <SFML/Graphics.hpp>
#include <cmath>

class MoveableComponent
{
public:
	
	void centerHorizontal(sf::VideoMode const videoMode)
	{
		centerPosX = (float)videoMode.width / 2;
		updatePosition();
	}

	void centerVertical(sf::VideoMode const videoMode)
	{
		centerPosY = (float)videoMode.height / 2;
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

	void snapToHorizontal(sf::VideoMode const videoMode, int sections, int sectionToSnapTo)
	{
		float sizePerSection = (float)videoMode.width / (float)sections;
		float rightOfSelectedSection = sectionToSnapTo * sizePerSection;
		float leftOfSelectedSection = (sectionToSnapTo - 1) * sizePerSection;
		float centerOfSelectedSection = (rightOfSelectedSection + leftOfSelectedSection) / 2;
		centerPosX = centerOfSelectedSection;
		updatePosition();
	}

	void snapToRightOffScreen(sf::VideoMode const videoMode)
	{
		centerPosX = videoMode.width + (totalWidth/2);
		updatePosition();
	}

	void snapToLeftOffScreen(sf::VideoMode const videoMode)
	{
		centerPosX = 0 - (totalWidth / 2);
		updatePosition();
	}

	void snapToBottomOffScreen(sf::VideoMode const videoMode)
	{
		centerPosY = videoMode.height + (totalHeight / 2);
		updatePosition();
	}

	void snapToTopOffScreen(sf::VideoMode const videoMode)
	{
		centerPosY = 0 - (totalHeight / 2);
		updatePosition();
	}

	void snapToBottom(sf::VideoMode const videoMode)
	{
		centerPosY = videoMode.height - (totalHeight/2);
		updatePosition();
	}

	void snapToTop(sf::VideoMode const videoMode)
	{
		centerPosY = totalHeight / 2;
		updatePosition();
	}

	void moveTo(float x, float y)
	{
		centerPosX = x;
		centerPosY = y;
		updatePosition();
	}

	void shiftVertical(float y)
	{
		centerPosY += y;
		updatePosition();
	}

	void shiftHorizontal(float x)
	{
		centerPosX += x;
		updatePosition();
	}

	void shiftTowards(float x, float y, float velocity)
	{
		float diffX = centerPosX - x;
		float diffY = centerPosY - y;
		float angle = std::atanf(diffX / diffY);
		float distance = std::hypotf(diffX, diffY);
		distance -= velocity;
		if (distance <= 0)
		{
			centerPosX = x;
			centerPosY = y;
			updatePosition();
			return;
		}

		float newDiffX = distance * std::sin(angle);
		float newDiffY = distance * std::cos(angle);
		shiftHorizontal(newDiffX - diffX);
		shiftVertical(newDiffY - diffY);
		updatePosition();
		return;
	}

	bool didCollideWithWindowEdge(sf::VideoMode videoMode)
	{
		if (didCollideWithTopWindowEdge(videoMode)) return true;
		if (didCollideWithBottomWindowEdge(videoMode)) return true;
		if (getLeftPosXToCenter() <= 0) return true;
		if (getRightPosXToCenter() >= videoMode.width) return true;

		return false;
	}

	bool didCollideWithBottomWindowEdge(sf::VideoMode videoMode)
	{
		 return getBottomPosYToCenter() >= videoMode.height;
	}

	bool didCollideWithTopWindowEdge(sf::VideoMode videoMode)
	{
		return getTopPosYToCenter() <= 0;
	}

	bool isPositionInMyArea(sf::Vector2i position)
	{
		if (position.y <= getTopPosYToCenter()) return false;
		if (position.y >= getBottomPosYToCenter()) return false;
		if (position.x <= getLeftPosXToCenter()) return false;
		if (position.x >= getRightPosXToCenter()) return false;

		return true;
	}

	bool isOffScreen(sf::VideoMode videoMode)
	{
		if (getBottomPosYToCenter() < 0) return true;
		if (getTopPosYToCenter() > videoMode.height) return true;
		if (isLeftOfScreen(videoMode)) return true;
		if (getLeftPosXToCenter() > videoMode.width) return true;

		return false;
	}

	bool isLeftOfScreen(sf::VideoMode videoMode)
	{
		return getRightPosXToCenter() < 0;
	}

	virtual void drawTo(sf::RenderWindow& window) = 0;

	

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
