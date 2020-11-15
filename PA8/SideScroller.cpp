#include "SideScroller.h"

const float gravitationalAcceleration = 0.001f;
const float playerUpwardsAcceleration = -2*gravitationalAcceleration;
const unsigned short int obstaclesPerScreen = 5;

SideScroller::SideScroller(sf::VideoMode vm)
{
	videoMode = vm;
	float playerSideLength = 0.05f * (float)videoMode.height;
	playerShape = new MoveableRectangle(sf::Vector2f(playerSideLength, playerSideLength), sf::Color::Green);
	playerShape->snapToHorizontal(videoMode, 4, 1);
	playerShape->snapToVertical(videoMode, 5, 3);
	verticalVelocity = 0.002f;
	isPlayerMoving = true;
	generateStartingObstacles();
	horizontalVelocity = -0.5f;
	isGameOver = false;
	shouldGoBackToMainMenu = false;
	score = 0;
	displayedScore = new TextComponent("Leander.ttf", std::to_string(score));
	displayedScore->snapToVertical(videoMode, 10, 1);
	displayedScore->snapToHorizontal(videoMode, 10, 1);
	displayedScore->setColor(sf::Color::Green);
}

SideScroller::~SideScroller()
{
	delete playerShape;
	playerShape = nullptr;
	delete displayedScore;
	displayedScore = nullptr;
}

void SideScroller::drawTo(sf::RenderWindow& window)
{
	playerShape->drawTo(window);
	for (std::list<MoveableRectangle*>::iterator i = obstacles.begin(); i != obstacles.end(); ++i)
	{
		(*i)->drawTo(window);
	}
	
	if (!obstacles.empty() && obstacles.front()->isLeftOfScreen(videoMode))
	{
		obstacles.pop_front();
		obstacles.push_back(generateObstacle());
		score++;
		displayedScore->setText(std::to_string(score));
	}

	displayedScore->drawTo(window);
}

void SideScroller::processKeyboardInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		shouldGoBackToMainMenu = true;
	}

	if (isGameOver) return;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		isPlayerMoving = true;
		verticalVelocity += playerUpwardsAcceleration;
	}
}

void SideScroller::processMousePosition(sf::Vector2i mouseWindowPosition)
{
}

void SideScroller::processMouseClick()
{
}

bool SideScroller::shouldExitGame()
{
	return shouldGoBackToMainMenu;
}

void SideScroller::updateState()
{
	if (isGameOver) return;

	updatePlayerState();
	updateObstacleState();
	checkForCollisions();
}

void SideScroller::handleEvents(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

MoveableRectangle* SideScroller::generateObstacle()
{
	std::random_device rdev{};
	static std::default_random_engine e{ rdev() };
	static std::uniform_real_distribution<float> d{ 0.25f , 0.65f };
	static std::uniform_int_distribution<int> c{ 0,1 };
	float randomHeight = (float)videoMode.height*d(e);
	bool isDown = (bool)c(e);
	MoveableRectangle* newObstacle = new MoveableRectangle(sf::Vector2f(0.05f * (float)videoMode.height, randomHeight), sf::Color::Cyan);
	newObstacle->snapToRightOffScreen(videoMode);
	if (isDown)
	{
		newObstacle->snapToBottom(videoMode);
	}
	else {
		newObstacle->snapToTop(videoMode);
	}
	return newObstacle;
}

void SideScroller::updatePlayerState()
{
	verticalVelocity += gravitationalAcceleration;
	if (playerShape->didCollideWithBottomWindowEdge(videoMode) && verticalVelocity > 0)
	{
		verticalVelocity = verticalVelocity * (-0.9f);
	}

	if (playerShape->didCollideWithTopWindowEdge(videoMode) && verticalVelocity < 0)
	{
		verticalVelocity = verticalVelocity * (-0.9f);
	}

	playerShape->shiftVertical(verticalVelocity);
}

void SideScroller::generateStartingObstacles()
{
	for (int i = 0; i < obstaclesPerScreen; i++)
	{
		obstacles.push_back(generateObstacle());
	}

	unsigned short int k = 1;

	for (std::list<MoveableRectangle*>::iterator i = obstacles.begin(); i != obstacles.end(); ++i)
	{
		(*i)->snapToHorizontal(videoMode, obstaclesPerScreen, obstaclesPerScreen + k++);
	}
}

void SideScroller::updateObstacleState()
{
	for (std::list<MoveableRectangle*>::iterator i = obstacles.begin(); i != obstacles.end(); ++i)
	{
		(*i)->shiftHorizontal(horizontalVelocity);
	}
}

void SideScroller::checkForCollisions()
{
	for (std::list<MoveableRectangle*>::iterator i = obstacles.begin(); i != obstacles.end(); ++i)
	{
		if ((*i)->didCollideWithOtherComponent(*playerShape))
		{
			isGameOver = true;
			break;
		}
	}
}
