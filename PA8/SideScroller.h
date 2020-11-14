#ifndef SIDE_SCROLLER_H
#define SIDE_SCROLLER_H

#include "Screen.h"
#include "MoveableRectangle.h"
#include <SFML/Graphics.hpp>
#include <cmath>

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
	void updateState(sf::VideoMode videoMode);

private:

	MoveableRectangle* playerShape;
	float verticalVelocity;
	bool isPlayerMoving;
};

#endif // !SIDE_SCROLLER_H
