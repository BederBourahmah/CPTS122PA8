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
	if (!castleTexture.loadFromFile("assets/castle.png"))
	{
		std::cout << "Failed to load castle texture." << std::endl;
	}

	if (!ghostTextures[(int)GhostAnimation::TailUp].loadFromFile("assets/ghostTailUp.png"))
	{
		std::cout << "Failed to load ghostTailUp texture." << std::endl;
	}

	if (!ghostTextures[(int)GhostAnimation::TailDown].loadFromFile("assets/ghostTailDown.png"))
	{
		std::cout << "Failed to load ghostTailDown texture." << std::endl;
	}

	if (!ghostTextures[(int)GhostAnimation::Death1].loadFromFile("assets/ghostDeath1.png"))
	{
		std::cout << "Failed to load ghostDeath1 texture." << std::endl;
	}

	if (!ghostTextures[(int)GhostAnimation::Death2].loadFromFile("assets/ghostDeath2.png"))
	{
		std::cout << "Failed to load ghostDeath2 texture." << std::endl;
	}

	if (!ghostTextures[(int)GhostAnimation::Death3].loadFromFile("assets/ghostDeath3.png"))
	{
		std::cout << "Failed to load ghostDeath3 texture." << std::endl;
	}

	if (!ghostTextures[(int)GhostAnimation::Death4].loadFromFile("assets/ghostDeath4.png"))
	{
		std::cout << "Failed to load ghostDeath4 texture." << std::endl;
	}

	if (!ghostTextures[(int)GhostAnimation::Death5].loadFromFile("assets/ghostDeath5.png"))
	{
		std::cout << "Failed to load ghostDeath5 texture." << std::endl;
	}

	playerBase = new MoveableRectangle(sf::Vector2f(vm.height*0.1f, vm.height * 0.1f), &castleTexture);
	playerBase->centerHorizontal(videoMode);
	playerBase->centerVertical(videoMode);
	shouldGoBackToMainMenu = false;
	currentEnemyId = INT16_MIN;
	generateEnemy();
	
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

	for (std::list<Enemy*>::iterator i = enemies.begin(); i != enemies.end(); ++i)
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
				for (std::list<Enemy*>::iterator i = enemies.begin(); i != enemies.end(); ++i)
				{
					if ((*i)->isPositionInMyArea(event.mouseButton.x, event.mouseButton.y))
					{
						//enemiesToDestroy.push((*i)->getId());
						(*i)->die();
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

	for (std::list<Enemy*>::iterator i = enemies.begin(); i != enemies.end(); ++i)
	{
		if ((*i)->getIsDead())
		{
			enemiesToDestroy.push((*i)->getId());
		}
		else if (!(*i)->getIsDying())
		{
			(*i)->shiftTowards((float)videoMode.width / 2.0f, (float)videoMode.height / 2.0f, distanceTravelled());
		}
		(*i)->setTimeElapsed(timeElapsed.asMicroseconds());
	}

	checkForCollisions();
}

void SwarmDefense::generateEnemy()
{
	Enemy* newEnemy = new Enemy(videoMode, currentEnemyId++, ghostTextures);
	try
	{
		enemies.push_front(newEnemy);
	}
	catch (const std::exception& ex)
	{
		std::cout << "Failed to generate enemy: " << ex.what() << std::endl;
	}
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
		std::list<Enemy*>::iterator itemToDelete = enemies.begin();
		for (std::list<Enemy*>::iterator i = enemies.begin(); i != enemies.end(); ++i)
		{
			if ((*i)->getId() == idToDelete)
			{
				itemToDelete = i;
				delete (*i);
			}
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
	for (std::list<Enemy*>::iterator i = enemies.begin(); i != enemies.end(); ++i)
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