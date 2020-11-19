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
	virtual void handleEvents(sf::RenderWindow& window) = 0;
	virtual void updateState() = 0;
	virtual void setIsLoading(bool newStatus)
	{
		isLoading = newStatus;
	}

protected:
	bool isLoading = false;
};

#endif // !SCREEN_H
