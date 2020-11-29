#include "Projectile.h"

Projectile::Projectile(sf::VideoMode vm, int newId) : MoveableRectangle(sf::Vector2f(0.042f * vm.width, 0.026 * vm.width))
{
	//moveToRandomEdgescreenPos(vm);
	
	//Center the projectile
	centerHorizontal(vm);
	centerVertical(vm);

	//Initializations
	id = newId;
	hasHit = false;
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

