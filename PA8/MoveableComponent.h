#ifndef MOVEABLE_COMPONENT_H
#define MOVEABLE_COMPONENT_H

#include <SFML/Graphics.hpp>
#include <cmath>

/// <summary>
/// This is a base class to be inherited by any component that can be moved. It contains convenience functions for moving the component to various
/// locations on the screen.
/// </summary>
class MoveableComponent
{
public:
	
	/// <summary>
	/// Centers the component along the horizontal axis.
	/// </summary>
	/// <param name="videoMode">The video mode that is rendering the component.</param>
	void centerHorizontal(sf::VideoMode const videoMode)
	{
		centerPosX = (float)videoMode.width / 2;
		updatePosition();
	}

	/// <summary>
	/// Centers the component along the vertical axis.
	/// </summary>
	/// <param name="videoMode">The video mode that is rendering this component.</param>
	void centerVertical(sf::VideoMode const videoMode)
	{
		centerPosY = (float)videoMode.height / 2;
		updatePosition();
	}

	/// <summary>
	/// Snaps the component to the vertical center of the provided section. Example: videoMode.height = 100, sections = 2, sectionToSnapTo = 1.
	/// These inputs will cause the component to center itself vertically at 25 pixels from the top, which is the vertical center of
	/// the top half of the screen.
	/// </summary>
	/// <param name="videoMode">The video mode that is rendering this component.</param>
	/// <param name="sections">The number of sections to divide the screen into.</param>
	/// <param name="sectionToSnapTo">The number of the section to snap to.</param>
	void snapToVertical(sf::VideoMode const videoMode, int sections, int sectionToSnapTo)
	{
		float sizePerSection = (float)videoMode.height / (float)sections;
		float bottomOfSelectedSection = sectionToSnapTo * sizePerSection;
		float topOfSelectedSection = (sectionToSnapTo - 1) * sizePerSection;
		float centerOfSelectedSection = (bottomOfSelectedSection + topOfSelectedSection) / 2;
		centerPosY = centerOfSelectedSection;
		updatePosition();
	}

	/// <summary>
	/// Snaps the component to the horizontal center of the provided section. Example: videoMode.width = 100, sections = 2, sectionToSnapTo = 1.
	/// These inputs will cause the component to center itself horizontally at 25 pixels from the left, which is the horizontal center of the
	/// left half of the screen.
	/// </summary>
	/// <param name="videoMode">The video mode that is rendering this component.</param>
	/// <param name="sections">The number of sections to divide the screen into.</param>
	/// <param name="sectionToSnapTo">The number of the section to snap to.</param>
	void snapToHorizontal(sf::VideoMode const videoMode, int sections, int sectionToSnapTo)
	{
		float sizePerSection = (float)videoMode.width / (float)sections;
		float rightOfSelectedSection = sectionToSnapTo * sizePerSection;
		float leftOfSelectedSection = (sectionToSnapTo - 1) * sizePerSection;
		float centerOfSelectedSection = (rightOfSelectedSection + leftOfSelectedSection) / 2;
		centerPosX = centerOfSelectedSection;
		updatePosition();
	}

	/// <summary>
	/// Moves this component just outside the right side of the screen.
	/// </summary>
	/// <param name="videoMode">The video mode that will render this component.</param>
	void snapToRightOffScreen(sf::VideoMode const videoMode)
	{
		centerPosX = videoMode.width + (totalWidth/2);
		updatePosition();
	}

	/// <summary>
	/// Moves this component just outside the left side of the screen.
	/// </summary>
	void snapToLeftOffScreen()
	{
		centerPosX = 0 - (totalWidth / 2);
		updatePosition();
	}

	/// <summary>
	/// Moves this component just outside the bottom side of the screen.
	/// </summary>
	/// <param name="videoMode">The video mode that will render this component.</param>
	void snapToBottomOffScreen(sf::VideoMode const videoMode)
	{
		centerPosY = videoMode.height + (totalHeight / 2);
		updatePosition();
	}

	/// <summary>
	/// Moves this component just outside the top side of the screen.
	/// </summary>
	void snapToTopOffScreen()
	{
		centerPosY = 0 - (totalHeight / 2);
		updatePosition();
	}

	/// <summary>
	/// Moves this component so it is inside the screen, but adjacent to the bottom side.
	/// </summary>
	/// <param name="videoMode">The video mode that will render this component.</param>
	void snapToBottom(sf::VideoMode const videoMode)
	{
		centerPosY = videoMode.height - (totalHeight/2);
		updatePosition();
	}

	/// <summary>
	/// Moves this component so it is inside the screen, but adjacent to the top side.
	/// </summary>
	void snapToTop()
	{
		centerPosY = totalHeight / 2;
		updatePosition();
	}

	/// <summary>
	/// Moves this component so it is inside the screen, but adjacent to the top side.
	/// </summary>
	void snapToLeft()
	{
		centerPosX = totalWidth / 2;
		updatePosition();
	}

	/// <summary>
	/// Moves this component so it is inside the screen, but adjacent to the right side.
	/// </summary>
	/// <param name="videoMode">The video mode that will render this component.</param>
	void snapToRight(sf::VideoMode const videoMode)
	{
		centerPosX = videoMode.width - totalWidth / 2;
		updatePosition();
	}

	/// <summary>
	/// Moves this component so it is inside the screen, but adjacent to the top and left sides, i.e. in top left corner.
	/// </summary>
	void snapToTopLeft()
	{
		snapToLeft();
		snapToTop();
	}

	/// <summary>
	/// Moves this component to the provided coordinates.
	/// </summary>
	/// <param name="x">The x-axis coordinate.</param>
	/// <param name="y">The y-axis coordinate.</param>
	void moveTo(float x, float y)
	{
		centerPosX = x;
		centerPosY = y;
		updatePosition();
	}

	/// <summary>
	/// Shifts this components vertically from its current position by the provided number of pixels.
	/// </summary>
	/// <param name="y">Number of pixels to shift the component along the y-axis.</param>
	void shiftVertical(float y)
	{
		centerPosY += y;
		updatePosition();
	}

	/// <summary>
	/// Shifts this components horizontally from its current position by the provided number of pixels.
	/// </summary>
	/// <param name="x">Number of pixels to shift the component along the x-axis.</param>
	void shiftHorizontal(float x)
	{
		centerPosX += x;
		updatePosition();
	}

	/// <summary>
	/// Shifts this components towards the provided coordinate by the provided number of pixels.
	/// </summary>
	/// <param name="x">The x-axis coordinate.</param>
	/// <param name="y">The y-axis coordinate.</param>
	/// <param name="distanceToShift">The number of pixels to shift.</param>
	void shiftTowards(float x, float y, float distanceToShift)
	{
		float diffX = centerPosX - x;
		float diffY = centerPosY - y;
		float angle = std::atan(diffX / diffY);
		float distance = std::hypotf(diffX, diffY);
		distance -= distanceToShift;
		if (distance <= 0)
		{
			centerPosX = x;
			centerPosY = y;
			updatePosition();
			return;
		}

		float newDiffX = distance * std::sin(angle);
		float newDiffY = distance * std::cos(angle);
		if (diffY < 0 && newDiffY > 0)
		{
			newDiffY *= -1.0f;
			newDiffX *= -1.0f;
		}
		shiftHorizontal(newDiffX - diffX);
		shiftVertical(newDiffY - diffY);
		updatePosition();
		return;
	}

	/// <summary>
	/// Returns true if this component is currently touching or has passed any window edge.
	/// </summary>
	/// <param name="videoMode">The video mode that is rendering this component.</param>
	/// <returns>True if this component is currently touching any window edge.</returns>
	bool didCollideWithWindowEdge(sf::VideoMode videoMode)
	{
		if (didCollideWithTopWindowEdge()) return true;
		if (didCollideWithBottomWindowEdge(videoMode)) return true;
		if (getLeftPosXToCenter() <= 0) return true;
		if (getRightPosXToCenter() >= videoMode.width) return true;

		return false;
	}

	/// <summary>
	/// Returns true if this component is currently touching or has passed the bottom window edge.
	/// </summary>
	/// <param name="videoMode">The video mode that is rendering this component.</param>
	/// <returns>True if this component is currently touching the bottom window edge.</returns>
	bool didCollideWithBottomWindowEdge(sf::VideoMode videoMode)
	{
		 return getBottomPosYToCenter() >= videoMode.height;
	}

	/// <summary>
	/// Returns true if this component is currently touching or has passed the top window edge.
	/// </summary>
	/// <returns>True if this component is currently touching the top window edge.</returns>
	bool didCollideWithTopWindowEdge()
	{
		return getTopPosYToCenter() <= 0;
	}

	/// <summary>
	/// Returns true if the provided position is within the bounds of this component.
	/// </summary>
	/// <param name="position">The position to check if it overlaps with this component.</param>
	/// <returns>True if the provided position is within the bounds of this component.</returns>
	bool isPositionInMyArea(sf::Vector2i position)
	{
		if (position.y <= getTopPosYToCenter()) return false;
		if (position.y >= getBottomPosYToCenter()) return false;
		if (position.x <= getLeftPosXToCenter()) return false;
		if (position.x >= getRightPosXToCenter()) return false;

		return true;
	}

	/// <summary>
	/// Returns true if the provided position is within the bounds of this component.
	/// </summary>
	/// <param name="x">The x-axis coordinate of the position to check.</param>
	/// <param name="y">The y-axis coordinate of the position to check.</param>
	/// <returns>True if the provided position is within the bounds of this component.</returns>
	bool isPositionInMyArea(int x, int y)
	{
		if (y <= getTopPosYToCenter()) return false;
		if (y >= getBottomPosYToCenter()) return false;
		if (x <= getLeftPosXToCenter()) return false;
		if (x >= getRightPosXToCenter()) return false;

		return true;
	}

	/// <summary>
	/// Returns true if this component is off screen.
	/// </summary>
	/// <param name="videoMode">The video mode that will render this component.</param>
	/// <returns>True if this component is off screen.</returns>
	bool isOffScreen(sf::VideoMode videoMode)
	{
		if (getBottomPosYToCenter() < 0) return true;
		if (getTopPosYToCenter() > videoMode.height) return true;
		if (isLeftOfScreen()) return true;
		if (getLeftPosXToCenter() > videoMode.width) return true;

		return false;
	}

	/// <summary>
	/// Returns true if this component is off screen and to the left of it.
	/// </summary>
	/// <returns>True if this component is off screen and to the left of it.</returns>
	bool isLeftOfScreen()
	{
		return getRightPosXToCenter() < 0;
	}

	/// <summary>
	/// Gets the coordinates of the center of this component.
	/// </summary>
	/// <returns>The coordinates of the center of this component.</returns>
	sf::Vector2f getCenterCoordinates()
	{
		return sf::Vector2f(centerPosX, centerPosY);
	}

	/// <summary>
	/// Draws this components to the provided window.
	/// </summary>
	/// <param name="window">The window to draw this component to.</param>
	virtual void drawTo(sf::RenderWindow& window) = 0;
	

protected:

	/// <summary>
	/// Updates the position of all subcomponents that comprise this component such that they are correctly positioned relative to the current
	/// center coordinate.
	/// </summary>
	virtual void updatePosition()=0;

	/// <summary>
	/// Gets the y-axis coordinate of the top of this component.
	/// </summary>
	/// <returns>The y-axis coordinate of the top of this component.</returns>
	float getTopPosYToCenter()
	{
		return centerPosY - (totalHeight / 2);
	}

	/// <summary>
	/// Gets the x-axis coordinate of the left side of this component.
	/// </summary>
	/// <returns>The x-axis coordinate of the left side of this component.</returns>
	float getLeftPosXToCenter()
	{
		return centerPosX - (totalWidth / 2);
	}

	/// <summary>
	/// Gets the y-axis coordinate of the bottom side of this component.
	/// </summary>
	/// <returns>The y-axis coordinate of the bottom side of this component.</returns>
	float getBottomPosYToCenter()
	{
		return centerPosY + (totalHeight / 2);
	}

	/// <summary>
	/// Gets the x-axis coordinate of the right side of this component.
	/// </summary>
	/// <returns>The x-axis coordinate of the right side of this component.</returns>
	float getRightPosXToCenter()
	{
		return centerPosX + (totalWidth / 2);
	}

	/// <summary>
	/// The x-axis coordinate of the center of this component.
	/// </summary>
	float centerPosX;

	/// <summary>
	/// The y-axis coordinate of the center of this component.
	/// </summary>
	float centerPosY;

	/// <summary>
	/// The total width of this component in pixels.
	/// </summary>
	float totalWidth;

	/// <summary>
	/// The total height of this component in pixels.
	/// </summary>
	float totalHeight;
	
};

#endif // !MOVEABLE_COMPONENT_H
