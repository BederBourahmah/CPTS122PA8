#ifndef ENEMY_H
#define ENEMY_H

#include "MoveableRectangle.h"
#include <SFML/Graphics.hpp>
#include <random>

class Enemy : public MoveableRectangle
{
public:
	Enemy(sf::VideoMode vm, int newId, sf::Texture* gTxtrs);
	~Enemy();

	int getId();

private:
	void moveToRandomEdgescreenPos(sf::VideoMode vm);
	int id;
	sf::Texture* ghostTextures;
};

#endif // !ENEMY_H
