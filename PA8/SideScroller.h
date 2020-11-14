#ifndef SIDE_SCROLLER_H
#define SIDE_SCROLLER_H

#include "Screen.h"
#include <SFML/Graphics.hpp>

class SideScroller : public Screen
{
public:

	SideScroller();

	void drawTo(sf::RenderWindow& window);
	void processKeyboardInput();
	void processMousePosition(sf::Vector2i mouseWindowPosition);
	void processMouseClick();
	bool shouldExitGame();

private:

	sf::RectangleShape playerShape;
};

#endif // !SIDE_SCROLLER_H
