#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include "WeaponType.h"

class SwarmDefense;

class Weapon
{
public:
	/// <summary>
	/// Initializes a new Weapon which fires the given pc (projectileCount) once every given fp (firingPeriod).
	/// </summary>
	/// <param name="fp">The time this weapon waits in microseconds between each time it fires.</param>
	/// <param name="pc">The number of projectiles this weapon fires each time.</param>
	Weapon(sf::Int64 fp, unsigned char pc, SwarmDefense* swarmDefense, void(SwarmDefense::* generateProjectileCallback)(unsigned char count));

	~Weapon();

	/// <summary>
	/// Updates the time elapsed since the last iteration. Will trigger this weapon to fire if cumulative time elapsed crosses a firingPeriod threshold.
	/// </summary>
	/// <param name="timeElapsed">The time in microseconds that have elapsed since the last iteration.</param>
	void setTimeElapsed(sf::Int64 timeElapsed);

private:
	/// <summary>
	/// The time this weapon waits in microseconds between each time it fires.
	/// </summary>
	sf::Int64 firingPeriod;

	/// <summary>
	/// Stores the cumulative time elapsed until the firingPeriod is reached, at which point its value is decreased by firingPeriod and this weapon fires.
	/// </summary>
	sf::Int64 microSecondsElapsed;

	/// <summary>
	/// The number of projectiles this weapon fires each time.
	/// </summary>
	unsigned char projectileCount;

	/// <summary>
	/// The parent component. Used as reference for the callback function.
	/// </summary>
	SwarmDefense* parent;

	/// <summary>
	/// The callback function for generating a projectile in the parent component.
	/// </summary>
	void(SwarmDefense::* onGenerateProjectile)(unsigned char count);
};

#endif // !WEAPON_H
