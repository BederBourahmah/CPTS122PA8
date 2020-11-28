#ifndef ENEMY_H
#define ENEMY_H

#include "MoveableRectangle.h"
#include <SFML/Graphics.hpp>
#include <random>
#include "GhostAnimation.h"

/// <summary>
/// A ghost enemy for the swarm defender game.
/// </summary>
class Enemy : public MoveableRectangle
{
public:
	/// <summary>
	/// Initializes the enemy position and size and animation textures.
	/// </summary>
	/// <param name="vm">The video mode that will render this enemy.</param>
	/// <param name="newId">The unique ID of the enemy.</param>
	/// <param name="gTxtrs">A pointer to the array of textures containing the frames of the ghost animation.</param>
	Enemy(sf::VideoMode vm, int newId, sf::Texture* gTxtrs);

	~Enemy();

	/// <summary>
	/// Gets the unique ID of this enemy.
	/// </summary>
	/// <returns>The unique ID of this enemy.</returns>
	int getId();

	/// <summary>
	/// Updates the time elapsed since the last iteration. Will trigger an animation if cumulative time elapsed crosses a threshold.
	/// </summary>
	/// <param name="timeElapsed">The time in microseconds that have elapsed since the last iteration.</param>
	void setTimeElapsed(sf::Int64 timeElapsed);

	/// <summary>
	/// Sets a private boolean flag to true, initiating the dying process.
	/// </summary>
	void die();

	/// <summary>
	/// Gets the value of a private boolean flag that is set to true when this enemy has completed the dying process.
	/// </summary>
	/// <returns>True of this enemy has reached the end of the dying process.</returns>
	bool getIsDead();

	/// <summary>
	/// Gets the value of a private boolean flag that is set to true when this enemy has started dying.
	/// </summary>
	/// <returns>True if this enemy has started dying.</returns>
	bool getIsDying();

	/// <summary>
	/// Gets the value of a private boolean flag that is set to true when this enemy has completed the attacking process.
	/// </summary>
	/// <returns>True if this enemy has completed the attacking process.</returns>
	bool getDidAttack();

	/// <summary>
	/// Sets a private boolean flag to true, initiating the attacking process.
	/// </summary>
	void attack();

	/// <summary>
	/// Gets the value of a private boolean flag that is set to true when this enemy has started the attacking process.
	/// </summary>
	/// <returns>True if this enemy has started the attacking process.</returns>
	bool getIsAttacking();

private:
	/// <summary>
	/// Moves this enemy to a random spot just outside the screen and mirrors the base texture appropriately.
	/// </summary>
	/// <param name="vm">The video mode of the screen that will render this enemy.</param>
	void moveToRandomEdgescreenPos(sf::VideoMode vm);

	/// <summary>
	/// The unique ID of this enemy.
	/// </summary>
	int id;

	/// <summary>
	/// The pointer to the array of textures containing the various frames of the ghost animation.
	/// </summary>
	sf::Texture* ghostTextures;

	/// <summary>
	/// Stores the cumulative time elapsed until the frame period is reached, at which point its value is decreased by that period.
	/// </summary>
	sf::Int64 microSecondsElapsed;

	/// <summary>
	/// The current ghost animation texture frame displayed.
	/// </summary>
	GhostAnimation currentAnimation;

	/// <summary>
	/// Changes the current animation frame according to various boolean flags.
	/// </summary>
	void animate();

	/// <summary>
	/// Whether this enemy has started the dying process.
	/// </summary>
	bool isDying;

	/// <summary>
	/// Whether this enemy has completed the dying process.
	/// </summary>
	bool isDead;

	/// <summary>
	/// Whether this enemy has started the attacking process.
	/// </summary>
	bool isAttacking;

	/// <summary>
	/// Whether this enemy has completed the attacking process.
	/// </summary>
	bool didAttack;

	/// <summary>
	/// Updates the currently rendered texture to match the current animation enum.
	/// </summary>
	void updateAnimationFrame();

	/// <summary>
	/// The refresh interval for the animations.
	/// </summary>
	sf::Int64 refreshInterval;

	/// <summary>
	/// Whether this enemy is mirrored based on their position relative to center.
	/// </summary>
	bool isMirrored;
};

#endif // !ENEMY_H
