#include "MainMenu.h"
#include "VideoHelpers.h"
#include <iostream>

MainMenu::MainMenu(sf::VideoMode const videoMode)
{
	sideScrollerText = new TextComponent("Leander.ttf", "Side Scroller Game");
	swarmDefenderText = new TextComponent("Leander.ttf", "Swarm Defender Game");
	exitText = new TextComponent("Leander.ttf", "Exit Game");
	selector = new MenuSelector(swarmDefenderText->getWidth(), swarmDefenderText->getHeight());
	sideScrollerText->centerHorizontal(videoMode);
	sideScrollerText->snapToVertical(videoMode, 5, 2);
	swarmDefenderText->centerHorizontal(videoMode);
	swarmDefenderText->snapToVertical(videoMode, 5, 3);
	exitText->centerHorizontal(videoMode);
	exitText->snapToVertical(videoMode, 5, 4);
	currentSelection = MainMenuSelection::SideScroller;
	updateSelectorPosition();
	if (!loadMainMenuBackgroundSprite(videoMode))
	{
		std::cout << "Failed to load background sprite." << std::endl;
	}
	selectedScreen = Screens::MainMenu;
	modal = new IpAddressInputModal(videoMode);
	server = nullptr;
}

MainMenu::~MainMenu()
{
	delete sideScrollerText;
	sideScrollerText = nullptr;
	delete swarmDefenderText;
	swarmDefenderText = nullptr;
	delete exitText;
	exitText = nullptr;
	delete selector;
	selector = nullptr;
	delete server;
	server = nullptr;
}

void MainMenu::drawTo(sf::RenderWindow &window)
{
	window.draw(backgroundSprite);
	sideScrollerText->drawTo(window);
	swarmDefenderText->drawTo(window);
	exitText->drawTo(window);
	selector->drawTo(window);
	if (modal != nullptr)
	{
		modal->drawTo(window);
	}
}

void MainMenu::moveSelectorDown()
{
	if (currentSelection == MainMenuSelection::SideScroller)
	{
		currentSelection = MainMenuSelection::SwarmDefender;
		updateSelectorPosition();
		return;
	}

	currentSelection = MainMenuSelection::Exit;
	updateSelectorPosition();
	return;
}

void MainMenu::moveSelectorUp()
{
	if (currentSelection == MainMenuSelection::Exit)
	{
		currentSelection = MainMenuSelection::SwarmDefender;
		updateSelectorPosition();
		return;
	}

	currentSelection = MainMenuSelection::SideScroller;
	updateSelectorPosition();
	return;
}

void MainMenu::processKeyboardInput()
{
	if (modal != nullptr) return;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		switch (currentSelection)
		{
		case MainMenuSelection::SideScroller:
			selectedScreen = Screens::SideScroller;
			break;
		case MainMenuSelection::SwarmDefender:
			selectedScreen = Screens::SwarmDefense;
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
	if (modal != nullptr) return;

	if (sideScrollerText->isPositionInMyArea(mouseWindowPosition))
	{
		currentSelection = MainMenuSelection::SideScroller;
		updateSelectorPosition();
		return;
	}

	if (swarmDefenderText->isPositionInMyArea(mouseWindowPosition))
	{
		currentSelection = MainMenuSelection::SwarmDefender;
		updateSelectorPosition();
		return;
	}

	if (exitText->isPositionInMyArea(mouseWindowPosition))
	{
		currentSelection = MainMenuSelection::Exit;
		updateSelectorPosition();
		return;
	}
}

void MainMenu::processMouseClick()
{
	if (modal != nullptr) return;
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) return;

	sf::Vector2i mousePosition = sf::Mouse::getPosition();
	if (sideScrollerText->isPositionInMyArea(mousePosition))
	{
		currentSelection = MainMenuSelection::SideScroller;
		updateSelectorPosition();
		selectedScreen = Screens::SideScroller;
		return;
	}

	if (swarmDefenderText->isPositionInMyArea(mousePosition))
	{
		currentSelection = MainMenuSelection::SwarmDefender;
		updateSelectorPosition();
		selectedScreen = Screens::SwarmDefense;
		return;
	}

	if (exitText->isPositionInMyArea(mousePosition))
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

void MainMenu::handleEvents(sf::RenderWindow& window)
{
	if (modal != nullptr)
	{
		modal->handleEvents(window);
		return;
	}

	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) window.close();

		if (event.type == sf::Event::KeyPressed)
		{
			handleKeyPressEvent(event);
		}
	}
}

void MainMenu::updateState()
{
	if (modal != nullptr)
	{
		modal->updateState();
		if (modal->getIsReady())
		{
			std::string addr = modal->getAddress();
			unsigned int port = modal->getPort();
			std::cout << addr << " : " << port << std::endl;
			server = new TcpServer(port);
			//TODO attempt to connect to network client
			delete modal;
			modal = nullptr;

		}
	}
}

void MainMenu::updateSelectorPosition()
{
	switch (currentSelection)
	{
	case MainMenuSelection::SideScroller:
		selector->moveTo(sideScrollerText->getCenterPosX(), sideScrollerText->getCenterPosY());
		return;
	case MainMenuSelection::SwarmDefender:
		selector->moveTo(swarmDefenderText->getCenterPosX(), swarmDefenderText->getCenterPosY());
		return;
	case MainMenuSelection::Exit:
		selector->moveTo(exitText->getCenterPosX(), exitText->getCenterPosY());
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

void MainMenu::handleKeyPressEvent(sf::Event event)
{
	if (event.type != sf::Event::KeyPressed) return;

	if (event.key.code == sf::Keyboard::Down)
	{
		moveSelectorDown();
		return;
	}

	if (event.key.code == sf::Keyboard::Up)
	{
		moveSelectorUp();
		return;
	}
}
