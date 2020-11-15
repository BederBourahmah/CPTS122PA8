#include "SwarmDefense.h"

const static float enemyVelocity = 0.1f;

SwarmDefense::SwarmDefense(sf::VideoMode vm)
{
	videoMode = vm;
	playerBase = new MoveableRectangle(sf::Vector2f(vm.height*0.1, vm.height * 0.1), sf::Color::Green);
	playerBase->centerHorizontal(videoMode);
	playerBase->centerVertical(videoMode);
	shouldGoBackToMainMenu = false;
	currentEnemyId = INT16_MIN;
	generateEnemy();
	displayedScore = new TextComponent("Leander.ttf", std::to_string(score));
	displayedScore->snapToVertical(videoMode, 10, 1);
	displayedScore->snapToHorizontal(videoMode, 10, 1);
	displayedScore->setColor(sf::Color::Green);
}

SwarmDefense::~SwarmDefense()
{
	delete playerBase;
	playerBase = nullptr;
	delete displayedScore;
	displayedScore = nullptr;
}

void SwarmDefense::drawTo(sf::RenderWindow& window)
{
	displayedScore->setText(std::to_string(score));
	playerBase->drawTo(window);
	displayedScore->drawTo(window);
	for (std::list<MoveableRectangle*>::iterator i = enemies.begin(); i != enemies.end(); ++i)
	{
		(*i)->drawTo(window);
	}
}

void SwarmDefense::processKeyboardInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		shouldGoBackToMainMenu = true;
	}
}

void SwarmDefense::processMousePosition(sf::Vector2i mouseWindowPosition)
{
}

void SwarmDefense::processMouseClick()
{
}

bool SwarmDefense::shouldExitGame()
{
	return shouldGoBackToMainMenu;
}

void SwarmDefense::handleEvents(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) window.close();

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				for (std::list<MoveableRectangle*>::iterator i = enemies.begin(); i != enemies.end(); ++i)
				{
					if ((*i)->isPositionInMyArea(event.mouseButton.x, event.mouseButton.y))
					{
						enemiesToDestroy.push((*i)->getId());
						score++;
					}
				}
			}
		}
	}
}

void SwarmDefense::updateState()
{
	while (!enemiesToDestroy.empty())
	{
		if (enemies.empty())
		{
			enemiesToDestroy.pop();
			continue;
		}
		
		int idToDelete = enemiesToDestroy.front();
		std::list<MoveableRectangle*>::iterator itemToDelete = enemies.begin();
		for (std::list<MoveableRectangle*>::iterator i = enemies.begin(); i != enemies.end(); ++i)
		{
			if ((*i)->getId() == idToDelete) break;

			++itemToDelete;
		}

		enemies.erase(itemToDelete);
		enemiesToDestroy.pop();
		generateEnemy();
		generateEnemy();
	}

	for (std::list<MoveableRectangle*>::iterator i = enemies.begin(); i != enemies.end(); ++i)
	{
		(*i)->shiftTowards(videoMode.width / 2, videoMode.height / 2, enemyVelocity);
	}
}

void SwarmDefense::generateEnemy()
{
	float enemySideLength = 0.025f * (float)videoMode.height;
	std::random_device rdev{};
	static std::default_random_engine randomEngine{ rdev() };
	static std::uniform_real_distribution<float> realDistribution{ 0.00f , 1.00f };
	static std::uniform_int_distribution<int> integerDistrubution{ 0,1 };
	float randomPercent = realDistribution(randomEngine);
	bool isDown = (bool)integerDistrubution(randomEngine);
	bool isRight = (bool)integerDistrubution(randomEngine);
	bool isVerticalShift = (bool)integerDistrubution(randomEngine);
	MoveableRectangle* newEnemy = new MoveableRectangle(sf::Vector2f(enemySideLength, enemySideLength), sf::Color::Cyan, currentEnemyId++);
	if (isDown)
	{
		newEnemy->snapToBottomOffScreen(videoMode);
	}
	else {
		newEnemy->snapToTopOffScreen(videoMode);
	}

	if (isRight)
	{
		newEnemy->snapToRightOffScreen(videoMode);
	}
	else {
		newEnemy->snapToLeftOffScreen(videoMode);
	}

	float shift = 0;
	if (isVerticalShift)
	{
		shift = isDown ? -randomPercent * videoMode.height : randomPercent * videoMode.height;
		newEnemy->shiftVertical(shift);
	}
	else {
		shift = isRight ? -randomPercent * videoMode.width : randomPercent * videoMode.width;
		newEnemy->shiftHorizontal(shift);
	}

	enemies.push_back(newEnemy);
}
