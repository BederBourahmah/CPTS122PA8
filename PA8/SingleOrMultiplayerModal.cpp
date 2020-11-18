#include "SingleOrMultiplayerModal.h"

SingleOrMultiplayerModal::SingleOrMultiplayerModal(sf::VideoMode vm) : Modal(ModalSize::Small, vm)
{
	singlePlayerButton = new TextComponent("Leander.ttf", "Single Player", 18);
	singlePlayerButton->centerHorizontal(vm);
	singlePlayerButton->snapToVertical(vm, 6, 3);
	multiPlayerButton = new TextComponent("Leander.ttf", "Network Game", 18);
	multiPlayerButton->centerHorizontal(vm);
	multiPlayerButton->snapToVertical(vm, 6, 4);
	isReady = false;
	isSinglePlayerSelected = true;
}

SingleOrMultiplayerModal::~SingleOrMultiplayerModal()
{
	delete singlePlayerButton;
	singlePlayerButton = nullptr;
	delete multiPlayerButton;
	multiPlayerButton = nullptr;
}

void SingleOrMultiplayerModal::drawTo(sf::RenderWindow& window)
{
	Modal::drawTo(window);
	singlePlayerButton->drawTo(window);
	multiPlayerButton->drawTo(window);
}

void SingleOrMultiplayerModal::handleEvents(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
			continue;
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				processMouseClick(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			}
			continue;
		}
	}
}

bool SingleOrMultiplayerModal::getIsSinglePlayer()
{
	return isSinglePlayerSelected;
}

bool SingleOrMultiplayerModal::getIsReady()
{
	return isReady;
}

void SingleOrMultiplayerModal::processMouseClick(sf::Vector2i mousePosition)
{
	if (singlePlayerButton->isPositionInMyArea(mousePosition))
	{
		isSinglePlayerSelected = true;
		isReady = true;
		return;
	}

	if (multiPlayerButton->isPositionInMyArea(mousePosition))
	{
		isSinglePlayerSelected = false;
		isReady = true;
		return;
	}
}
