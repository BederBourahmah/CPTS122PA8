#ifndef SWARM_DEFENSE_H
#define SWARM_DEFENSE_H

#include "Screen.h"
#include "MoveableRectangle.h"
#include "TextComponent.h"
#include <SFML/Graphics.hpp>
#include <list>
#include <random>
#include <queue>
#include <cmath>
#include <iostream>
#include "Enemy.h"
#include "GhostAnimation.h"

class ScreenManager;

class SwarmDefense : public Screen
{
public:

	SwarmDefense(
		sf::VideoMode vm,
		bool mp,
		ScreenManager* manager,
		void(ScreenManager::* sendEnemiesCallback)(sf::Uint16 numberOfEnemies),
		sf::Uint16(ScreenManager::* getEnemiesCallback)()
		);
	~SwarmDefense();

	void drawTo(sf::RenderWindow& window);
	void processKeyboardInput();
	void processMousePosition(sf::Vector2i mouseWindowPosition);
	bool shouldExitGame();
	void handleEvents(sf::RenderWindow& window);
	void updateState();
	void purchase(int Price);

private:
	int currentEnemyId;
	MoveableRectangle* playerBase;
	sf::VideoMode videoMode;
	bool shouldGoBackToMainMenu;
	std::list<Enemy*> enemies;
	void generateEnemy();
	std::queue<int> enemiesToDestroy;
	int enemiesCollided;
	TextComponent* displayedScore;
	TextComponent* displayedHealth;
	TextComponent* displayedCoins;
	unsigned int score;
	unsigned int coins;
	unsigned short int health;
	void destroyEnemies();
	void checkForCollisions();
	bool isGameOver;
	bool isMultiplayer;
	ScreenManager* parentManager;
	void(ScreenManager::* onSendEnemies)(sf::Uint16 numberOfEnemies);
	sf::Uint16(ScreenManager::* onGetEnemies)();
	float unitOfDistance;
	float distanceTravelled();
	sf::Clock clock;
	sf::Time timeElapsed;
	sf::Texture castleTexture;
	sf::Texture ghostTextures[14];
};

#endif // !SWARM_DEFENSE_H
