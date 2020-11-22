#include "Enemy.h"

Enemy::Enemy(sf::VideoMode vm, int newId, sf::Texture* gTxtrs) : MoveableRectangle(sf::Vector2f(0.042f*vm.width, 0.026*vm.width))
{
	isMirrored = false;
	moveToRandomEdgescreenPos(vm);
	id = newId;
	ghostTextures = gTxtrs;
	currentAnimation = GhostAnimation::TailUp;
	setTexture(&ghostTextures[(int)currentAnimation]);
	isDying = false;
	isDead = false;
	refreshInterval = 500000;
}

Enemy::~Enemy()
{
}

int Enemy::getId()
{
	return id;
}

void Enemy::setTimeElapsed(sf::Int64 timeElapsed)
{
	microSecondsElapsed += timeElapsed;
	if (isDying || isAttacking)
	{
		refreshInterval = 200000;
	}
	
	if (microSecondsElapsed > refreshInterval)
	{
		microSecondsElapsed -= refreshInterval;
		animate();
		return;
	}
}

void Enemy::die()
{
	isDying = true;
}

bool Enemy::getIsDead()
{
	return isDead;
}

bool Enemy::getIsDying()
{
	return isDying;
}

bool Enemy::getDidAttack()
{
	return didAttack;
}

void Enemy::attack()
{
	isAttacking = true;
}

bool Enemy::getIsAttacking()
{
	return isAttacking;
}

void Enemy::animate()
{
	updateAnimationFrame();
	setTexture(&ghostTextures[(int)currentAnimation]);
}

void Enemy::updateAnimationFrame()
{
	if (isDying)
	{
		switch (currentAnimation)
		{
		case GhostAnimation::Death1:
			currentAnimation = GhostAnimation::Death2;
			return;
		case GhostAnimation::Death2:
			currentAnimation = GhostAnimation::Death3;
			return;
		case GhostAnimation::Death3:
			currentAnimation = GhostAnimation::Death4;
			return;
		case GhostAnimation::Death4:
			currentAnimation = GhostAnimation::Death5;
			return;
		case GhostAnimation::Death5:
			isDead = true;
			return;
		case GhostAnimation::TailDown:
		case GhostAnimation::TailUp:
			updateDimensions(sf::Vector2f(totalWidth * 0.85f, totalHeight * 1.2f), sf::Vector2f(-0.15f*totalWidth, 0.2f * totalHeight));
			if (isMirrored) mirror();
			
			currentAnimation = GhostAnimation::Death1;
			return;
		default:
			currentAnimation = GhostAnimation::Death1;
			return;
		}
	}

	if (isAttacking)
	{
		switch (currentAnimation)
		{
		case GhostAnimation::Attack1:
			currentAnimation = GhostAnimation::Attack2;
			return;
		case GhostAnimation::Attack2:
			currentAnimation = GhostAnimation::Attack3;
			return;
		case GhostAnimation::Attack3:
			currentAnimation = GhostAnimation::Attack4;
			return;
		case GhostAnimation::Attack4:
			currentAnimation = GhostAnimation::Attack5;
			return;
		case GhostAnimation::Attack5:
			currentAnimation = GhostAnimation::Attack6;
			return;
		case GhostAnimation::Attack6:
			currentAnimation = GhostAnimation::Attack7;
			return;
		case GhostAnimation::Attack7:
			didAttack = true;
			updateDimensions(sf::Vector2f(totalWidth * 1.0526f, totalHeight * 0.6756f), sf::Vector2f(0.0f, -0.3244f*totalHeight));
			currentAnimation = GhostAnimation::Death1;
			if (isMirrored) mirror();

			return;
		default:
			updateDimensions(sf::Vector2f(totalWidth * 0.95f, totalHeight * 1.48f), sf::Vector2f(0.0f, totalHeight * 0.48f));
			currentAnimation = GhostAnimation::Attack1;
			if (isMirrored) mirror();

			return;
		}
	}

	if (currentAnimation == GhostAnimation::TailUp)
	{
		currentAnimation = GhostAnimation::TailDown;
		return;
	}

	currentAnimation = GhostAnimation::TailUp;
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

	if (isLeftOfCenter((float)vm.width / 2.0f))
	{
		mirror();
		isMirrored = true;
	}
}
