#include "Weapon.h"

Weapon::Weapon(sf::Int64 fp, unsigned char pc, SwarmDefense* swarmDefense, void(SwarmDefense::* generateProjectileCallback)(unsigned char count))
{
	firingPeriod = fp;
	projectileCount = pc;
	parent = swarmDefense;
	onGenerateProjectile = generateProjectileCallback;
	microSecondsElapsed = 0;
}

Weapon::~Weapon()
{
}

void Weapon::setTimeElapsed(sf::Int64 timeElapsed)
{
	microSecondsElapsed += timeElapsed;
	if (microSecondsElapsed > firingPeriod)
	{
		microSecondsElapsed -= firingPeriod;
		((*parent).*onGenerateProjectile)(projectileCount);
	}
}
