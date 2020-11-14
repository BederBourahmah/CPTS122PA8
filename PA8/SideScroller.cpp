#include "SideScroller.h"

SideScroller::SideScroller()
{
	playerShape = sf::RectangleShape(sf::Vector2f(50, 50));
	playerShape.setFillColor(sf::Color::Green);
}

void SideScroller::drawTo(sf::RenderWindow& window)
{
	window.draw(playerShape);
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
