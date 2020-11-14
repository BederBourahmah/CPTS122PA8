#include "SideScroller.h"

SideScroller::SideScroller(sf::VideoMode videoMode)
{
	playerShape = new MoveableRectangle(sf::Vector2f(50, 50), sf::Color::Green);
	playerShape->snapToHorizontal(videoMode, 4, 1);
	playerShape->snapToVertical(videoMode, 5, 3);
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
