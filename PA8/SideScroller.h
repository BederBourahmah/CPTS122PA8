#ifndef SIDE_SCROLLER_H
#define SIDE_SCROLLER_H

#include "Screen.h"
#include "MoveableRectangle.h"
#include "TextComponent.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <list>
#include <random>

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
	bool isPlayerMoving;
	std::list<MoveableRectangle*> obstacles;
	MoveableRectangle* generateObstacle();
	float horizontalVelocity;
	void updatePlayerState();
	sf::VideoMode videoMode;
	void generateStartingObstacles();
	void updateObstacleState();
	bool isGameOver;
	void checkForCollisions();
	bool shouldGoBackToMainMenu;
	unsigned int score;
	TextComponent* displayedScore;
};

#endif // !SIDE_SCROLLER_H
