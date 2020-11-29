#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "MoveableRectangle.h"
#include <SFML/Graphics.hpp>
#include <random>

/// <summary>
/// A Projectile for the swarm defender game.
/// </summary>
class Projectile : public MoveableRectangle
{
public:
	/// <summary>
	/// Initializes the Projectile position and size and animation textures.

	/// <param name="vm">The video mode that will render this Projectile.</param>
	/// <param name="newId">The unique ID of the Projectile.</param>
	/// <param name="gTxtrs">A pointer to the array of textures containing the frames of the ghost animation.</param>
	Projectile(sf::VideoMode vm, int newId, float inpx, float inpy);

	~Projectile();

	
	/// Gets the unique ID of this Projectile.
	int getId();

	/// <summary>
	/// Indicates the projectile has found and hit a target

	void hit();

	/// <summary>
	/// Gets the value of a private boolean flag that is set to true when this Projectile has hit a target.

	/// <returns>True of this Projectile has reached the end of the dying process.</returns>
	bool getHasHit();

	//Getters for dest
	float getxDest();
	float getyDest();

	

private:
	
	int id;
	bool hasHit;

	//Provides "destination" vectors which the projectile will shift towards
	float xdest;
	float ydest;

};

#endif 
