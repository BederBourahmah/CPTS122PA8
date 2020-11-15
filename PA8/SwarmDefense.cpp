#include "SwarmDefense.h"

SwarmDefense::SwarmDefense(sf::VideoMode vm)
{
	videoMode = vm;
	playerBase = new MoveableRectangle(sf::Vector2f(vm.height*0.1, vm.height * 0.1), sf::Color::Green);
	playerBase->centerHorizontal(videoMode);
	playerBase->centerVertical(videoMode);
	shouldGoBackToMainMenu = false;
}

SwarmDefense::~SwarmDefense()
{
	delete playerBase;
	playerBase = nullptr;
}

void SwarmDefense::drawTo(sf::RenderWindow& window)
{
	playerBase->drawTo(window);
}

void SwarmDefense::processKeyboardInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		shouldGoBackToMainMenu = true;
	}
}

void SwarmDefense::processMousePosition(sf::Vector2i mouseWindowPosition)
{
}

void SwarmDefense::processMouseClick()
{
}

bool SwarmDefense::shouldExitGame()
{
	return shouldGoBackToMainMenu;
}

void SwarmDefense::handleEvents(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}
