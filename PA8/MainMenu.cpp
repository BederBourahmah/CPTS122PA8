#include "MainMenu.h"
#include "VideoHelpers.h"
#include <iostream>

MainMenu::MainMenu(sf::VideoMode const vm, ScreenManager *manager, void(ScreenManager::* connectToNetworkCallback)(std::string addr, unsigned int port, bool isServer))
{
	isSingleVsMultiplayerModalDisplayed = false;
	isNetworkConnectionModalDisplayed = false;
	videoMode = vm;
	howToPlayText = new TextComponent("Leander.ttf", "How To Play");
	swarmDefenderText = new TextComponent("Leander.ttf", "Swarm Defender Game");
	exitText = new TextComponent("Leander.ttf", "Exit Game");
	selector = new MenuSelector(swarmDefenderText->getWidth(), swarmDefenderText->getHeight());
	howToPlayText->centerHorizontal(videoMode);
	howToPlayText->snapToVertical(videoMode, 5, 3);
	swarmDefenderText->centerHorizontal(videoMode);
	swarmDefenderText->snapToVertical(videoMode, 5, 2);
	exitText->centerHorizontal(videoMode);
	exitText->snapToVertical(videoMode, 5, 4);
	currentSelection = MainMenuSelection::SwarmDefender;
	updateSelectorPosition();
	if (!loadMainMenuBackgroundSprite(videoMode))
	{
		std::cout << "Failed to load background sprite." << std::endl;
	}
	selectedScreen = Screens::MainMenu;
	networkConnectionModal = new IpAddressInputModal(videoMode);
	singVsMultiModal = new SingleOrMultiplayerModal(videoMode);
	onConnectToNetwork = connectToNetworkCallback;
	parentManager = manager;
}

MainMenu::~MainMenu()
{
	delete howToPlayText;
	howToPlayText = nullptr;
	delete swarmDefenderText;
	swarmDefenderText = nullptr;
	delete exitText;
	exitText = nullptr;
	delete selector;
	selector = nullptr;
	delete singVsMultiModal;
	singVsMultiModal = nullptr;
	delete networkConnectionModal;
	networkConnectionModal = nullptr;
}

void MainMenu::drawTo(sf::RenderWindow &window)
{
	window.draw(backgroundSprite);
	howToPlayText->drawTo(window);
	swarmDefenderText->drawTo(window);
	exitText->drawTo(window);
	selector->drawTo(window);
	if (isNetworkConnectionModalDisplayed && networkConnectionModal != nullptr) networkConnectionModal->drawTo(window);
		
	if (isSingleVsMultiplayerModalDisplayed) singVsMultiModal->drawTo(window);
}

void MainMenu::moveSelectorDown()
{
	if (currentSelection == MainMenuSelection::SwarmDefender)
	{
		currentSelection = MainMenuSelection::HowToPlayMenu;
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
		currentSelection = MainMenuSelection::HowToPlayMenu;
		updateSelectorPosition();
		return;
	}

	currentSelection = MainMenuSelection::SwarmDefender;
	updateSelectorPosition();
	return;
}

void MainMenu::processKeyboardInput()
{
	if (isMenuDisabled()) return;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		switch (currentSelection)
		{
		case MainMenuSelection::HowToPlayMenu:
			selectedScreen = Screens::HowToPlayMenu;
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
	if (isMenuDisabled()) return;

	if (howToPlayText->isPositionInMyArea(mouseWindowPosition))
	{
		currentSelection = MainMenuSelection::HowToPlayMenu;
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
	if (isNetworkConnectionModalDisplayed && networkConnectionModal != nullptr)
	{
		networkConnectionModal->handleEvents(window);
		return;
	}

	if (isSingleVsMultiplayerModalDisplayed && singVsMultiModal != nullptr)
	{
		singVsMultiModal->handleEvents(window);
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

		if (event.type == sf::Event::MouseButtonReleased)
		{
			handleClickEvent(event);
		}
	}
}

void MainMenu::updateState()
{
	if (isNetworkConnectionModalDisplayed && networkConnectionModal != nullptr)
	{
		networkConnectionModal->updateState();
		if (networkConnectionModal->getIsReady())
		{
			handleConnectToNetwork();
			return;
		}

		if (networkConnectionModal->getIsCancelling())
		{
			closeNetworkConnectionModal();
		}
	}

	if (isSingleVsMultiplayerModalDisplayed && singVsMultiModal != nullptr)
	{
		if (singVsMultiModal->getIsReady())
		{
			if (singVsMultiModal->getIsSinglePlayer())
			{
				closeSingleVsMultiplayerModal();
				currentSelection = MainMenuSelection::SwarmDefender;
				updateSelectorPosition();
				selectedScreen = Screens::SwarmDefense;
				return;
			}
			else
			{
				isNetworkConnectionModalDisplayed = true;
				closeSingleVsMultiplayerModal();
				return;
			}
		}

		if (singVsMultiModal->getIsCancelling())
		{
			closeSingleVsMultiplayerModal();
			return;
		}
	}
}

void MainMenu::updateSelectorPosition()
{
	switch (currentSelection)
	{
	case MainMenuSelection::HowToPlayMenu:
		selector->moveTo(howToPlayText->getCenterPosX(), howToPlayText->getCenterPosY());
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

void MainMenu::handleConnectToNetwork()
{
	std::string addr = networkConnectionModal->getAddress();
	unsigned int port = networkConnectionModal->getPort();
	bool isServer = networkConnectionModal->getIsServer();
	((*parentManager).*onConnectToNetwork)(addr, port, isServer);
	
	closeNetworkConnectionModal();
}

bool MainMenu::isMenuDisabled()
{
	return isNetworkConnectionModalDisplayed || isSingleVsMultiplayerModalDisplayed || isLoading;
}

void MainMenu::closeSingleVsMultiplayerModal()
{
	isSingleVsMultiplayerModalDisplayed = false;
	singVsMultiModal->resetState();
}

void MainMenu::closeNetworkConnectionModal()
{
	networkConnectionModal->resetState();
	isNetworkConnectionModalDisplayed = false;
}

void MainMenu::handleClickEvent(sf::Event event)
{
	if (event.type != sf::Event::MouseButtonReleased || isMenuDisabled() || event.mouseButton.button != sf::Mouse::Left) 
		return;

	sf::Vector2i mousePosition(event.mouseButton.x, event.mouseButton.y);
	if (howToPlayText->isPositionInMyArea(mousePosition))
	{
		currentSelection = MainMenuSelection::HowToPlayMenu;
		updateSelectorPosition();
		selectedScreen = Screens::HowToPlayMenu;
		return;
	}

	if (swarmDefenderText->isPositionInMyArea(mousePosition))
	{
		isSingleVsMultiplayerModalDisplayed = true;
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
