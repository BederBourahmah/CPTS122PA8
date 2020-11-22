#ifndef ENEMY_H
#define ENEMY_H

#include "MoveableRectangle.h"
#include <SFML/Graphics.hpp>
#include <random>
#include "GhostAnimation.h"

class Enemy : public MoveableRectangle
{
public:
	Enemy(sf::VideoMode vm, int newId, sf::Texture* gTxtrs);
	~Enemy();

	int getId();
	void setTimeElapsed(sf::Int64 timeElapsed);
	void die();
	bool getIsDead();
	bool getIsDying();

private:
	void moveToRandomEdgescreenPos(sf::VideoMode vm);
	int id;
	sf::Texture* ghostTextures;
	sf::Int64 microSecondsElapsed;
	GhostAnimation currentAnimation;
	void animate();
	bool isDying;
	bool isDead;
	void updateAnimationFrame();
	sf::Int64 refreshInterval;
};

#endif // !ENEMY_H
