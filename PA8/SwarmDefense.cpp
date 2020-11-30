#include "SwarmDefense.h"
#include <iostream>

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
	isShopModalDisplayed = false;
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

	if (!ghostTextures[(int)GhostAnimation::Attack1].loadFromFile("assets/ghostAttack1.png"))
	{
		std::cout << "Failed to load ghostAttack1 texture." << std::endl;
	}

	if (!ghostTextures[(int)GhostAnimation::Attack2].loadFromFile("assets/ghostAttack2.png"))
	{
		std::cout << "Failed to load ghostAttack2 texture." << std::endl;
	}

	if (!ghostTextures[(int)GhostAnimation::Attack3].loadFromFile("assets/ghostAttack3.png"))
	{
		std::cout << "Failed to load ghostAttack3 texture." << std::endl;
	}

	if (!ghostTextures[(int)GhostAnimation::Attack4].loadFromFile("assets/ghostAttack4.png"))
	{
		std::cout << "Failed to load ghostAttack4 texture." << std::endl;
	}

	if (!ghostTextures[(int)GhostAnimation::Attack5].loadFromFile("assets/ghostAttack5.png"))
	{
		std::cout << "Failed to load ghostAttack5 texture." << std::endl;
	}

	if (!ghostTextures[(int)GhostAnimation::Attack6].loadFromFile("assets/ghostAttack6.png"))
	{
		std::cout << "Failed to load ghostAttack6 texture." << std::endl;
	}

	if (!ghostTextures[(int)GhostAnimation::Attack7].loadFromFile("assets/ghostAttack7.png"))
	{
		std::cout << "Failed to load ghostAttack7 texture." << std::endl;
	}

	playerBase = new MoveableRectangle(sf::Vector2f(vm.height*0.1f, vm.height * 0.1f), &castleTexture);
	playerBase->centerHorizontal(videoMode);
	playerBase->centerVertical(videoMode);
	shouldGoBackToMainMenu = false;
	currentEnemyId = INT16_MIN;
	generateEnemy();
	
	displayedScore = new TextComponent("Leander.ttf", scorePrefix + std::to_string(score), 50, 1);
	displayedScore->snapToLeft();
	displayedScore->setColor(sf::Color::Green);
	
	health = 100;

	displayedHealth = new TextComponent("Leander.ttf", healthPrefix + std::to_string(health), 50, 1);
	displayedHealth->snapToLeft();
	displayedHealth->snapToVertical(videoMode, 10, 2);
	displayedHealth->setColor(sf::Color::Green);

	displayedCoins = new TextComponent("Leander.ttf", coinsPrefix + std::to_string(coins), 50, 1);
	displayedCoins->snapToLeft();
	displayedCoins->snapToVertical(videoMode, 10, 3);
	displayedCoins->setColor(sf::Color::Green);

	isGameOver = false;

	//Sounds

	if (!Hit.loadFromFile("assets/Hit.wav")) {
		std::cout << "Hit sound error";
	}
		
	if (!Explosion.loadFromFile("assets/Explosion.wav")) {
		std::cout << "Exp sound error";
	}

	if (!Lose.loadFromFile("assets/Lose.wav")) {
		std::cout << "Lose sound error";
	}

	////Music
	if (!music.openFromFile("assets/HHMega.ogg")) {
		std::cout << "Music error";
	}
	music.setVolume(40);
	music.play();
	

	isMultiplayer = mp;
	parentManager = manager;
	onSendEnemies = sendEnemiesCallback;
	onGetEnemies = getEnemiesCallback;
	enemiesCollided = 0;
	unitOfDistance = hypotf((float)videoMode.height, (float)videoMode.width)*0.01f;
	shopModal = new ShopModal(videoMode, this, &SwarmDefense::purchaseWeapon, &SwarmDefense::closeShopModal);
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
	delete shopModal;
	shopModal = nullptr;
}

void SwarmDefense::drawTo(sf::RenderWindow& window)
{
	std::string newScore = std::to_string(score);
	std::string newHealth = std::to_string(health);
	std::string newCoins = std::to_string(coins);

	displayedScore->setText(scorePrefix + newScore);
	displayedHealth->setText(healthPrefix + newHealth);
	displayedCoins->setText(coinsPrefix + newCoins);
	displayedScore->snapToLeft();
	displayedHealth->snapToLeft();
	displayedCoins->snapToLeft();

	playerBase->drawTo(window);
	if (!isGameOver)
	{
		displayedScore->drawTo(window);
		displayedHealth->drawTo(window);
		displayedCoins->drawTo(window);
	}
	

	//Draw projectiles
	for (std::list<Projectile*>::iterator i = projectiles.begin(); i != projectiles.end(); i++) {
		(*i)->drawTo(window);
}

	for (std::list<Enemy*>::iterator i = enemies.begin(); i != enemies.end(); ++i)
	{
		(*i)->drawTo(window);
	}

	if (isShopModalDisplayed)
	{
		shopModal->drawTo(window);
	}

	if (isGameOver)
	{
		displayedScore->drawTo(window);
		displayedHealth->drawTo(window);
		displayedCoins->drawTo(window);
	}
}

void SwarmDefense::processKeyboardInput()
{
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
	if (isShopModalDisplayed)
	{
		shopModal->handleEvents(window);
		return;
	}

	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) window.close();

		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
		{
			music.stop();
			shouldGoBackToMainMenu = true;
		}

		if (isGameOver) { 
			return;
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{


			if (event.mouseButton.button == sf::Mouse::Left)
			{
				float xpos = sf::Mouse::getPosition(window).x;
				float ypos = sf::Mouse::getPosition(window).y;

				Projectile* newProj = new Projectile(videoMode, 0, xpos, ypos);
				projectiles.push_back(newProj);
			}
		}

		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::S)
		{
			isShopModalDisplayed = true;
		}
	}
}

void SwarmDefense::updateState()
{
	if (isGameOver) { 
		if (!isGameOverMusic) {
			isGameOverMusic = true;
			music.stop();
			sound.setBuffer(Lose);
			sound.play();
		}
		return; 
	}
	timeElapsed = clock.restart();
	
	destroyEnemies();

	for (std::list<Enemy*>::iterator i = enemies.begin(); i != enemies.end(); ++i)
	{
		if (!(*i)->getIsDying())
		{
			if (!(*i)->getIsAttacking())
			{
				(*i)->shiftTowards((float)videoMode.width / 2.0f, (float)videoMode.height / 2.0f, distanceTravelled());
			}

			if ((*i)->getDidAttack())

			{
				health = health <= 1 ? 0 : health-1;
				enemiesCollided++;
				(*i)->die();

				//Play explosion sound
				sound.setBuffer(Explosion);
				sound.play();

				if (health == 0)
				{
					isGameOver = true;
				}
			}
		}

		if ((*i)->getIsDead())
		{
			enemiesToDestroy.push((*i)->getId());
		}

		(*i)->setTimeElapsed(timeElapsed.asMicroseconds());
	}

	for (std::list<Projectile*>::iterator i = projectiles.begin(); i != projectiles.end(); i++) {
		if (!(*i)->getHasHit())
		{
			(*i)->shiftTowards((*i)->getxDest(), (*i)->getyDest(), distanceTravelled() * 5);
		}
	}

	for (std::list<Weapon*>::iterator i = weapons.begin(); i != weapons.end(); ++i)
	{
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
			(*i)->attack();
		}


	}

	std::queue<std::list<Projectile*>::iterator> projectilesToDestroy;
	bool didFind = false;

	for (std::list<Projectile*>::iterator i = projectiles.begin(); i != projectiles.end(); i++) {
		for (std::list<Enemy*>::iterator j = enemies.begin(); j != enemies.end(); j++)
		{
			 MoveableRectangle* ptr = *i;
			if ((*j)->didCollideWithOtherComponent(*ptr))
			{
				projectilesToDestroy.push(i);
				delete (*i);

				if (!(*j)->getIsDying())
				{
					score++;
					coins += 10;

					//Hit sound
					sound.setBuffer(Hit);
					sound.play();
				}
				(*j)->die();
			}

		}


	}

	while (!projectilesToDestroy.empty())
	{
		std::list<Projectile*>::iterator projectile = projectilesToDestroy.front();
		projectiles.erase(projectile);
		projectilesToDestroy.pop();
	}

}


float SwarmDefense::distanceTravelled()
{
	return (float)timeElapsed.asMicroseconds() * enemyVelocity;
}

bool SwarmDefense::purchaseWeapon(unsigned int cost, WeaponType type)
{
	if (coins < cost) return false;
	
	coins -= cost;
	Weapon* newWeapon = nullptr;

	switch (type)
	{
	case WeaponType::Basic:
		newWeapon = new Weapon(1000000, 1, this, &SwarmDefense::generateProjectiles);
		weapons.push_back(newWeapon);
		break;
	default:
		break;
	}

	return true;
}

void SwarmDefense::closeShopModal()
{
	isShopModalDisplayed = false;
}

void SwarmDefense::generateProjectiles(unsigned char count)
{
	sf::Vector2f randomEnemyPosition;
	if (getPositionOfRandomEnemy(randomEnemyPosition))
	{
		fireProjectileAt(randomEnemyPosition);
	}
}

void SwarmDefense::fireProjectileAt(sf::Vector2f position)
{
	Projectile* newProj = new Projectile(videoMode, 0, position.x, position.y);
	projectiles.push_back(newProj);
}

bool SwarmDefense::getPositionOfRandomEnemy(sf::Vector2f& position)
{
	if (enemies.empty())
	{
		return false;
	}

	int numberOfEnemies = enemies.size();
	std::random_device rdev{};
	std::default_random_engine randomEngine{ rdev() };
	std::uniform_int_distribution<int> integerDistrubution{ 0, numberOfEnemies-1 };
	auto randomEnemyIndex = integerDistrubution(randomEngine);
	int index = 0;
	for (std::list<Enemy*>::iterator i = enemies.begin(); i != enemies.end(); ++i)
	{
		if (index++ == randomEnemyIndex)
		{
			position = (*i)->getCenterCoordinates();
			return true;
		}
	}
}
