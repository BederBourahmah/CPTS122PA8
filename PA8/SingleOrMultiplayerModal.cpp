#include "SingleOrMultiplayerModal.h"

SingleOrMultiplayerModal::SingleOrMultiplayerModal(sf::VideoMode vm) : Modal(ModalSize::Small, vm)
{
	singlePlayerButton = new TextComponent("Leander.ttf", "Single Player", 18);
	singlePlayerButton->centerHorizontal(vm);
	singlePlayerButton->snapToVertical(vm, 20, 8);
	multiPlayerButton = new TextComponent("Leander.ttf", "Network Game", 18);
	multiPlayerButton->centerHorizontal(vm);
	multiPlayerButton->snapToVertical(vm, 20, 11);
	cancelButton = new TextComponent("Leander.ttf", "Cancel", 18);
	cancelButton->centerHorizontal(vm);
	cancelButton->snapToVertical(vm, 20, 14);
	isReady = false;
	isSinglePlayerSelected = true;
	isCancelling = false;
}

SingleOrMultiplayerModal::~SingleOrMultiplayerModal()
{
	delete singlePlayerButton;
	singlePlayerButton = nullptr;
	delete multiPlayerButton;
	multiPlayerButton = nullptr;
	delete cancelButton;
	cancelButton = nullptr;
}

void SingleOrMultiplayerModal::drawTo(sf::RenderWindow& window)
{
	Modal::drawTo(window);
	singlePlayerButton->drawTo(window);
	multiPlayerButton->drawTo(window);
	cancelButton->drawTo(window);
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

		if (event.type == sf::Event::MouseButtonReleased)
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

bool SingleOrMultiplayerModal::getIsCancelling()
{
	return isCancelling;
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

	if (cancelButton->isPositionInMyArea(mousePosition))
	{
		isCancelling = true;
		return;
	}
}
