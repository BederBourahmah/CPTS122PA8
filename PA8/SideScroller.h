#ifndef SIDE_SCROLLER_H
#define SIDE_SCROLLER_H

#include "Screen.h"
#include "MoveableRectangle.h"
#include <SFML/Graphics.hpp>

class SideScroller : public Screen
{
public:

	SideScroller(sf::VideoMode videoMode);
	~SideScroller();

	void drawTo(sf::RenderWindow& window);
	void processKeyboardInput();
	void processMousePosition(sf::Vector2i mouseWindowPosition);
	void processMouseClick();
	bool shouldExitGame();
	void updateState();

private:

	MoveableRectangle* playerShape;
	float verticalVelocity;
};

#endif // !SIDE_SCROLLER_H
