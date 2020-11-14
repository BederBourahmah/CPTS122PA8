#include "MainMenu.h"
#include "VideoHelpers.h"
#include <iostream>

MainMenu::MainMenu(sf::VideoMode const videoMode)
{
	sideScroller = new TextComponent("Leander.ttf", "Side Scroller Game");
	exit = new TextComponent("Leander.ttf", "Exit Game");
	selector = new MenuSelector(sideScroller->getWidth(), sideScroller->getHeight());
	sideScroller->centerHorizontal(videoMode);
	sideScroller->snapToVertical(videoMode, 4, 2);
	exit->centerHorizontal(videoMode);
	exit->snapToVertical(videoMode, 4, 3);
	currentSelection = MainMenuSelection::SideScroller;
	updateSelectorPosition();
	if (!loadMainMenuBackgroundSprite(videoMode))
	{
		std::cout << "Failed to load background sprite." << std::endl;
	}
	selectedScreen = Screens::MainMenu;
}

MainMenu::~MainMenu()
{
	delete sideScroller;
	delete exit;
	delete selector;
}

void MainMenu::drawTo(sf::RenderWindow &window)
{
	window.draw(backgroundSprite);
	sideScroller->drawTo(window);
	exit->drawTo(window);
	selector->drawTo(window);
}

void MainMenu::moveSelectorDown()
{
	if (currentSelection == MainMenuSelection::SideScroller)
	{
		currentSelection = MainMenuSelection::Exit;
		updateSelectorPosition();
		return;
	}
}

void MainMenu::moveSelectorUp()
{
	if (currentSelection == MainMenuSelection::Exit)
	{
		currentSelection = MainMenuSelection::SideScroller;
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
		switch (currentSelection)
		{
		case MainMenuSelection::SideScroller:
			selectedScreen = Screens::SideScroller;
			break;
		case MainMenuSelection::Exit:
			selectedScreen = Screens::Exit;
			break;
		default:
			selectedScreen = Screens::MainMenu;
			break;
		}
	}
}

void MainMenu::processMousePosition(sf::Vector2i mouseWindowPosition)
{
	if (sideScroller->isPositionInMyArea(mouseWindowPosition))
	{
		currentSelection = MainMenuSelection::SideScroller;
		updateSelectorPosition();
		return;
	}

	if (exit->isPositionInMyArea(mouseWindowPosition))
	{
		currentSelection = MainMenuSelection::Exit;
		updateSelectorPosition();
		return;
	}
}

void MainMenu::processMouseClick()
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) return;

	sf::Vector2i mousePosition = sf::Mouse::getPosition();
	if (sideScroller->isPositionInMyArea(mousePosition))
	{
		//TODO: Implement sideScroller game
		return;
	}

	if (exit->isPositionInMyArea(mousePosition))
	{
		currentSelection = MainMenuSelection::Exit;
		updateSelectorPosition();
		selectedScreen = Screens::Exit;
		return;
	}
}

bool MainMenu::shouldExitGame()
{
	return selectedScreen == Screens::Exit;
}

Screens MainMenu::getSelectedScreen()
{
	return selectedScreen;
}

void MainMenu::updateSelectorPosition()
{
	switch (currentSelection)
	{
	case MainMenuSelection::SideScroller:
		selector->moveTo(sideScroller->getCenterPosX(), sideScroller->getCenterPosY());
		return;
	case MainMenuSelection::Exit:
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