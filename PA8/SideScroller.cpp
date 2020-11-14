#include "SideScroller.h"

const float verticalAcceleration = 0.001f;

SideScroller::SideScroller(sf::VideoMode videoMode)
{
	playerShape = new MoveableRectangle(sf::Vector2f(50, 50), sf::Color::Green);
	playerShape->snapToHorizontal(videoMode, 4, 1);
	playerShape->snapToVertical(videoMode, 5, 3);
	verticalVelocity = 0.002f;
	isPlayerMoving = true;
}

SideScroller::~SideScroller()
{
	delete playerShape;
	playerShape = nullptr;
}

void SideScroller::drawTo(sf::RenderWindow& window)
{
	playerShape->drawTo(window);
}

void SideScroller::processKeyboardInput()
{
}

void SideScroller::processMousePosition(sf::Vector2i mouseWindowPosition)
{
}

void SideScroller::processMouseClick()
{
}

bool SideScroller::shouldExitGame()
{
	return false;
}

void SideScroller::updateState(sf::VideoMode videoMode)
{
	if (!isPlayerMoving) return;
	
	verticalVelocity += verticalAcceleration;
	playerShape->shiftVertical(verticalVelocity);
	if (playerShape->didCollideWithWindowEdge(videoMode))
	{
		verticalVelocity = verticalVelocity * (-0.9f);
		if (std::abs(verticalVelocity) <= verticalAcceleration)
		{
			isPlayerMoving = false;
		}
	}
}
