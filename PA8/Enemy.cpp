#include "Enemy.h"

Enemy::Enemy(sf::VideoMode vm, int newId, sf::Texture* gTxtrs) : MoveableRectangle(sf::Vector2f(0.042f*vm.width, 0.026*vm.width))
{
	moveToRandomEdgescreenPos(vm);
	id = newId;
	ghostTextures = gTxtrs;
	setTexture(&gTxtrs[0]);
}

Enemy::~Enemy()
{
}

int Enemy::getId()
{
	return id;
}

void Enemy::moveToRandomEdgescreenPos(sf::VideoMode vm)
{
	std::random_device rdev{};
	static std::default_random_engine randomEngine{ rdev() };
	static std::uniform_real_distribution<float> realDistribution{ 0.00f , 1.00f };
	static std::uniform_int_distribution<int> integerDistrubution{ 0,1 };
	float randomPercent = realDistribution(randomEngine);
	bool isDown = (bool)integerDistrubution(randomEngine);
	bool isRight = (bool)integerDistrubution(randomEngine);
	bool isVerticalShift = (bool)integerDistrubution(randomEngine);

	if (isDown)
	{
		snapToBottomOffScreen(vm);
	}
	else {
		snapToTopOffScreen();
	}

	if (isRight)
	{
		snapToRightOffScreen(vm);
	}
	else {
		snapToLeftOffScreen();
	}

	float shift = 0;
	if (isVerticalShift)
	{
		shift = isDown ? -randomPercent * vm.height : randomPercent * vm.height;
		shiftVertical(shift);
	}
	else {
		shift = isRight ? -randomPercent * vm.width : randomPercent * vm.width;
		shiftHorizontal(shift);
	}

	if (isLeftOfCenter((float)vm.width / 2.0f)) mirror();
}
