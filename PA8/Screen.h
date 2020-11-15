#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>

class Screen
{
public:
	virtual void drawTo(sf::RenderWindow& window) = 0;
	virtual void processKeyboardInput() = 0;
	virtual void processMousePosition(sf::Vector2i mouseWindowPosition) = 0;
	virtual void processMouseClick() = 0;
	virtual bool shouldExitGame() = 0;
};

#endif // !SCREEN_H
