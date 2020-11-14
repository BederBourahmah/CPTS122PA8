#include "SideScroller.h"

const float gravitationalAcceleration = 0.001f;
const float playerUpwardsAcceleration = -2*gravitationalAcceleration;

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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		isPlayerMoving = true;
		verticalVelocity += playerUpwardsAcceleration;
	}
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
	verticalVelocity += gravitationalAcceleration;
	if (playerShape->didCollideWithBottomWindowEdge(videoMode) && verticalVelocity > 0)
	{
		verticalVelocity = verticalVelocity * (-0.9f);
	}

	if (playerShape->didCollideWithTopWindowEdge(videoMode) && verticalVelocity < 0)
	{
		verticalVelocity = verticalVelocity * (-0.9f);
	}

	playerShape->shiftVertical(verticalVelocity);
}
