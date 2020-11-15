#ifndef SWARM_DEFENSE_H
#define SWARM_DEFENSE_H

#include "Screen.h"
#include "MoveableRectangle.h"
#include <SFML/Graphics.hpp>
#include <list>
#include <random>
#include <queue>

class SwarmDefense : public Screen
{
public:

	SwarmDefense(sf::VideoMode vm);
	~SwarmDefense();

	void drawTo(sf::RenderWindow& window);
	void processKeyboardInput();
	void processMousePosition(sf::Vector2i mouseWindowPosition);
	void processMouseClick();
	bool shouldExitGame();
	void handleEvents(sf::RenderWindow& window);
	void updateState();

private:
	int currentEnemyId;
	MoveableRectangle* playerBase;
	sf::VideoMode videoMode;
	bool shouldGoBackToMainMenu;
	std::list<MoveableRectangle*> enemies;
	void generateEnemy();
	std::queue<int> enemiesToDestroy;
};

#endif // !SWARM_DEFENSE_H
