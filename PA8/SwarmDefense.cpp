#include "SwarmDefense.h"

const static float enemyVelocity = 0.0001f;
static const std::string scorePrefix = "Score: ";
static const std::string healthPrefix = "Health: ";
static const std::string coinsPrefix = "Coins: ";


SwarmDefense::SwarmDefense(
	sf::VideoMode vm,
	bool mp,
	ScreenManager* manager,
	void(ScreenManager::* sendEnemiesCallback)(sf::Uint16 numberOfEnemies),
	sf::Uint16(ScreenManager::* getEnemiesCallback)()
	)
{
	videoMode = vm;
	sf::Texture txtr;
	playerBase = new MoveableRectangle(sf::Vector2f(vm.height*0.1f, vm.height * 0.1f), "assets/castle.png");
	playerBase->centerHorizontal(videoMode);
	playerBase->centerVertical(videoMode);
	shouldGoBackToMainMenu = false;
	currentEnemyId = INT16_MIN;
	generateEnemy();
	
	//
	displayedScore = new TextComponent("Leander.ttf", scorePrefix + std::to_string(score), 50);
	displayedScore->snapToVertical(videoMode, 10, 1);
	displayedScore->setColor(sf::Color::Green);
	
	displayedHealth = new TextComponent("Leander.ttf", healthPrefix + std::to_string(health), 50);
	displayedHealth->snapToVertical(videoMode, 10, 2);
	displayedHealth->setColor(sf::Color::Green);

	displayedCoins = new TextComponent("Leander.ttf", coinsPrefix + std::to_string(coins), 50);
	displayedCoins->snapToVertical(videoMode, 10, 3);
	displayedCoins->setColor(sf::Color::Green);

	health = 100;
	isGameOver = false;
	isMultiplayer = mp;
	parentManager = manager;
	onSendEnemies = sendEnemiesCallback;
	onGetEnemies = getEnemiesCallback;
	enemiesCollided = 0;
	unitOfDistance = hypotf((float)videoMode.height, (float)videoMode.width)*0.01f;
	clock.restart();
}

SwarmDefense::~SwarmDefense()
{
	delete playerBase;
	playerBase = nullptr;
	delete displayedScore;
	displayedScore = nullptr;
	delete displayedCoins;
	displayedCoins = nullptr;
}

void SwarmDefense::drawTo(sf::RenderWindow& window)
{
	std::string newScore = std::to_string(score);
	std::string newHealth = std::to_string(health);
	std::string newCoins = std::to_string(coins);

	displayedScore->setText(scorePrefix + newScore);
	displayedHealth->setText(healthPrefix + newHealth);
	displayedCoins->setText(coinsPrefix + newCoins);


	playerBase->drawTo(window);
	displayedScore->drawTo(window);
	displayedHealth->drawTo(window);
	displayedCoins->drawTo(window);

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

		if (isGameOver) return;

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
						coins = coins + 10;

					}
				}
			}
		}
	}
}

void SwarmDefense::updateState()
{
	if (isGameOver) return;
	timeElapsed = clock.restart();
	
	destroyEnemies();

	for (std::list<MoveableRectangle*>::iterator i = enemies.begin(); i != enemies.end(); ++i)
	{
		(*i)->shiftTowards((float)videoMode.width / 2.0f, (float)videoMode.height / 2.0f, distanceTravelled());
	}

	checkForCollisions();
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
		newEnemy->snapToTopOffScreen();
	}

	if (isRight)
	{
		newEnemy->snapToRightOffScreen(videoMode);
	}
	else {
		newEnemy->snapToLeftOffScreen();
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

void SwarmDefense::destroyEnemies()
{
	sf::Uint16 enemiesDestroyed = 0;
	while (!enemiesToDestroy.empty())
	{
		if (enemies.empty())
		{
			try
			{
				enemiesToDestroy.pop();
			}
			catch (const std::exception& ex)
			{
				std::cout << "Error during pop when 'enemies' is empty: " << ex.what() << std::endl;
			}
			
			continue;
		}

		int idToDelete = enemiesToDestroy.front();
		std::list<MoveableRectangle*>::iterator itemToDelete = enemies.begin();
		for (std::list<MoveableRectangle*>::iterator i = enemies.begin(); i != enemies.end(); ++i)
		{
			if ((*i)->getId() == idToDelete) break;

			++itemToDelete;
		}

		try
		{
			enemies.erase(itemToDelete);
		}
		catch (const std::exception& ex)
		{
			std::cout << "Error during erase of an enemy: " << ex.what() << std::endl;
		}

		try
		{
			enemiesToDestroy.pop();
		}
		catch (const std::exception& ex)
		{
			std::cout << "Error during pop after erasing enemy: " << ex.what() << std::endl;
		}
		
		enemiesDestroyed++;
	}

	if (isMultiplayer)
	{
		if (enemiesDestroyed > enemiesCollided)
		{
			((*parentManager).*onSendEnemies)(enemiesDestroyed - enemiesCollided);
		}
		
		enemiesCollided += ((*parentManager).*onGetEnemies)();
	}
	else
	{
		enemiesCollided = enemiesDestroyed;
	}


	for (int i = 0; i < enemiesCollided * 2; i++)
	{
		generateEnemy();
	}
	
	enemiesCollided = 0;
}

void SwarmDefense::checkForCollisions()
{
	for (std::list<MoveableRectangle*>::iterator i = enemies.begin(); i != enemies.end(); ++i)
	{
		if ((*i)->didCollideWithOtherComponent(*playerBase))
		{
			enemiesToDestroy.push((*i)->getId());
			health--;
			enemiesCollided++;
			if (health == 0)
			{
				isGameOver = true;
			}
		}

	}
}

float SwarmDefense::distanceTravelled()
{
	return (float)timeElapsed.asMicroseconds() * enemyVelocity;
}

void SwarmDefense::purchase(int price) {
	coins = coins - price;
	//Add purchasing mechanism for shop later.
}