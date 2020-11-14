#include "MainMenu.h"
#include "VideoHelpers.h"
#include <iostream>

MainMenu::MainMenu(sf::VideoMode const videoMode)
{
	start = new TextComponent("Leander.ttf", "Start Game");
	exit = new TextComponent("Leander.ttf", "Exit Game");
	selector = new MenuSelector(start->getWidth(), start->getHeight());
	start->centerHorizontal(videoMode);
	start->snapToVertical(videoMode, 4, 2);
	exit->centerHorizontal(videoMode);
	exit->snapToVertical(videoMode, 4, 3);
	currentSelection = CurrentSelection::Start;
	updateSelectorPosition();
	if (!loadMainMenuBackgroundSprite(videoMode))
	{
		std::cout << "Failed to load background sprite." << std::endl;
	}
	isExitingGame = false;
}

MainMenu::~MainMenu()
{
	delete start;
	delete exit;
	delete selector;
}

void MainMenu::drawTo(sf::RenderWindow &window)
{
	window.draw(backgroundSprite);
	start->drawTo(window);
	exit->drawTo(window);
	selector->drawTo(window);
}

void MainMenu::moveSelectorDown()
{
	if (currentSelection == CurrentSelection::Start)
	{
		currentSelection = CurrentSelection::Exit;
		updateSelectorPosition();
		return;
	}
}

void MainMenu::moveSelectorUp()
{
	if (currentSelection == CurrentSelection::Exit)
	{
		currentSelection = CurrentSelection::Start;
		updateSelectorPosition();
		return;
	}
}

void MainMenu::processKeyboardInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		moveSelectorDown();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		moveSelectorUp();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if (currentSelection == CurrentSelection::Exit)
		{
			isExitingGame = true;
		}
	}
}

void MainMenu::processMousePosition(sf::Vector2i mouseWindowPosition)
{
	if (start->isPositionInMyArea(mouseWindowPosition))
	{
		currentSelection = CurrentSelection::Start;
		updateSelectorPosition();
		return;
	}

	if (exit->isPositionInMyArea(mouseWindowPosition))
	{
		currentSelection = CurrentSelection::Exit;
		updateSelectorPosition();
		return;
	}
}

void MainMenu::processMouseClick()
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) return;

	sf::Vector2i mousePosition = sf::Mouse::getPosition();
	if (start->isPositionInMyArea(mousePosition))
	{
		//TODO: Implement start game
		return;
	}

	if (exit->isPositionInMyArea(mousePosition))
	{
		currentSelection = CurrentSelection::Exit;
		updateSelectorPosition();
		isExitingGame = true;
		return;
	}
}

bool MainMenu::shouldExitGame()
{
	return isExitingGame;
}

void MainMenu::updateSelectorPosition()
{
	switch (currentSelection)
	{
	case CurrentSelection::Start:
		selector->moveTo(start->getCenterPosX(), start->getCenterPosY());
		return;
	case CurrentSelection::Exit:
		selector->moveTo(exit->getCenterPosX(), exit->getCenterPosY());
		return;
	default:
		return;
	}
}

const static float backgroundWidth = 3071;
const static float backgroundHeight = 2299;

bool MainMenu::loadMainMenuBackgroundTexture()
{
	if (!backgroundTexture.loadFromFile("assets/main_menu_background.jpg"))
	{
		return false;
	}
	return true;
}

bool MainMenu::loadMainMenuBackgroundSprite(sf::VideoMode const videoMode)
{
	if (!loadMainMenuBackgroundTexture())
	{
		return false;
	}

	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale((float)videoMode.width / backgroundWidth, (float)videoMode.height / backgroundHeight);
	return true;
}