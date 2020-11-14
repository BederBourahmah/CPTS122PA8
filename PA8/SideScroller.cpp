#include "SideScroller.h"

const float gravitationalAcceleration = 0.001f;
const float playerUpwardsAcceleration = -2*gravitationalAcceleration;

SideScroller::SideScroller(sf::VideoMode vm)
{
	videoMode = vm;
	float playerSideLength = 0.05f * (float)videoMode.height;
	playerShape = new MoveableRectangle(sf::Vector2f(playerSideLength, playerSideLength), sf::Color::Green);
	playerShape->snapToHorizontal(videoMode, 4, 1);
	playerShape->snapToVertical(videoMode, 5, 3);
	verticalVelocity = 0.002f;
	isPlayerMoving = true;
	obstacles = std::list<MoveableRectangle*>(1, generateObstacle());
	horizontalVelocity = -0.5f;
}

SideScroller::~SideScroller()
{
	delete playerShape;
	playerShape = nullptr;
}

void SideScroller::drawTo(sf::RenderWindow& window)
{
	playerShape->drawTo(window);
	for (std::list<MoveableRectangle*>::iterator i = obstacles.begin(); i != obstacles.end(); ++i)
	{
		(*i)->drawTo(window);
		
	}
	
	if (!obstacles.empty() && obstacles.front()->isOffScreen(videoMode))
	{
		obstacles.pop_front();
		obstacles.push_back(generateObstacle());
	}
}

void SideScroller::processKeyboardInput()
{
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
	return false;
}

void SideScroller::updateState()
{
	updatePlayerState();

	for (std::list<MoveableRectangle*>::iterator i = obstacles.begin(); i != obstacles.end(); ++i)
	{
		(*i)->shiftHorizontal(horizontalVelocity);
	}
}

MoveableRectangle* SideScroller::generateObstacle()
{
	std::random_device rdev{};
	static std::default_random_engine e{ rdev() };
	static std::uniform_real_distribution<float> d{ 0.25f , 0.75f };
	float randomHeight = (float)videoMode.height*d(e);
	MoveableRectangle* newObstacle = new MoveableRectangle(sf::Vector2f(50, randomHeight), sf::Color::Cyan);
	newObstacle->snapToHorizontal(videoMode, 4, 4);
	newObstacle->snapToBottom(videoMode);
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
