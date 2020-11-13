#include "MainMenu.h"

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
}

MainMenu::~MainMenu()
{
	delete start;
	delete exit;
	delete selector;
}

void MainMenu::draw(sf::RenderWindow &window)
{
	window.draw(start->getText());
	window.draw(exit->getText());
	selector->draw(window);
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

void MainMenu::updateSelectorPosition()
{
	switch (currentSelection)
	{
	case CurrentSelection::Start:
		selector->updatePosition(start->getCenterPosX(), start->getCenterPosY());
		return;
	case CurrentSelection::Exit:
		selector->updatePosition(exit->getCenterPosX(), exit->getCenterPosY());
		return;
	default:
		return;
	}
}
