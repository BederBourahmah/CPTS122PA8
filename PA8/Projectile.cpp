#include "Projectile.h"

Projectile::Projectile(sf::VideoMode vm, int newId, float inpx, float inpy) : MoveableRectangle(sf::Vector2f(0.021f * vm.width, 0.013 * vm.width))
{
	//moveToRandomEdgescreenPos(vm);
	
	//Center the projectile
	centerHorizontal(vm);
	centerVertical(vm);

	//Initializations
	id = newId;
	hasHit = false;
	xdest = inpx;
	ydest = inpy;
	//refreshInterval = 500000;
}

Projectile::~Projectile()
{
}

int Projectile::getId()
{
	return id;
}

void Projectile::hit() {
	hasHit = true;
}

bool Projectile::getHasHit() {
	return hasHit;
}

float Projectile::getxDest() {
	return xdest;
}
float Projectile::getyDest() {
	return ydest;
};

