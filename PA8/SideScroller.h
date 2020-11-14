#ifndef SIDE_SCROLLER_H
#define SIDE_SCROLLER_H

#include "Screen.h"

class SideScroller : public Screen
{
public:
	void drawTo(sf::RenderWindow& window);
	void processKeyboardInput();
	void processMousePosition(sf::Vector2i mouseWindowPosition);
	void processMouseClick();
	bool shouldExitGame();
};

#endif // !SIDE_SCROLLER_H
