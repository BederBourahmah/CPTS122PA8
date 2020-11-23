#include "HowToPlayMenu.h"

HowToPlayMenu::HowToPlayMenu(sf::VideoMode const vm)
{

}

HowToPlayMenu::~HowToPlayMenu()
{

}


void HowToPlayMenu::drawTo(sf::RenderWindow& window)
{
	window.draw(backgroundSprite);
	rulesText->drawTo(window);
	selector->drawTo(window);
}

void HowToPlayMenu::processKeyboardInput()
{
	if (isMenuDisabled()) return;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if (currentSelection == MainMenuSelection::Exit)
		{
			selectedScreen = Screens::Exit;
		}
	}
}

void HowToPlayMenu::processMousePosition(sf::Vector2i mouseWindowPosition)
{
	if (isMenuDisabled()) return;

	if (returnText->isPositionInMyArea(mouseWindowPosition))
	{
		currentSelection = MainMenuSelection::Exit;
		updateSelectorPosition();
		return;
	}
}

void HowToPlayMenu::processMouseClick()
{
	if (isMenuDisabled()) return;
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) return;

	sf::Vector2i mousePosition = sf::Mouse::getPosition();
	if (returnText->isPositionInMyArea(mousePosition))
	{
		currentSelection = MainMenuSelection::Exit;
		updateSelectorPosition();
		selectedScreen = Screens::Exit;
		return;
	}
}

bool HowToPlayMenu::shouldExitGame()
{
	return false;
}

void HowToPlayMenu::handleEvents(sf::RenderWindow& window)
{
	if (singVsMultiModal != nullptr)
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
	}
}

void HowToPlayMenu::updateState()
{
	if (isAttemptingToConnect)
	{
		loadingModal->updateState();
		attemptConnection();
		return;
	}

	if (networkConnectionModal != nullptr)
	{
		networkConnectionModal->updateState();
		if (networkConnectionModal->getIsReady())
		{
			handleConnectToNetwork();
		}
	}

	if (singVsMultiModal != nullptr)
	{
		if (singVsMultiModal->getIsReady())
		{
			if (singVsMultiModal->getIsSinglePlayer())
			{
				delete singVsMultiModal;
				singVsMultiModal = nullptr;
				currentSelection = MainMenuSelection::SwarmDefender;
				updateSelectorPosition();
				selectedScreen = Screens::SwarmDefense;
				return;
			}
			else
			{
				networkConnectionModal = new IpAddressInputModal(videoMode);
				delete singVsMultiModal;
				singVsMultiModal = nullptr;
				return;
			}
		}
	}
}

bool HowToPlayMenu::isMenuDisabled()
{
	return loadingModal != nullptr || networkConnectionModal != nullptr || singVsMultiModal != nullptr;
}

void HowToPlayMenu::updateSelectorPosition()
{
	if (currentSelection == MainMenuSelection::Exit)
	{
		selector->moveTo(returnText->getCenterPosX(), returnText->getCenterPosY());
	}
}

void HowToPlayMenu::handleKeyPressEvent(sf::Event event)
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

void HowToPlayMenu::attemptConnection()
{
	if (server != nullptr)
	{
		server->attemptToConnect();
		if (server->getDidConnect())
		{
			isAttemptingToConnect = false;
			delete loadingModal;
			loadingModal = nullptr;
		}
	}
	return;
}

void HowToPlayMenu::handleConnectToNetwork()
{
	std::string addr = networkConnectionModal->getAddress();
	unsigned int port = networkConnectionModal->getPort();
	bool isServer = networkConnectionModal->getIsServer();
	if (isServer)
	{
		server = new TcpServer(port);
	}
	else {
		client = new TcpClient(addr, port);
	}
	loadingModal = new LoadingModal(videoMode);

	isAttemptingToConnect = true;
	delete networkConnectionModal;
	networkConnectionModal = nullptr;
}

Screens HowToPlayMenu::getSelectedScreen()
{
	return selectedScreen;
}

void HowToPlayMenu::moveSelectorDown()
{
	if (currentSelection == MainMenuSelection::Exit)
	{
		currentSelection = MainMenuSelection::Exit;
		updateSelectorPosition();
		return;
	}

	currentSelection = MainMenuSelection::Exit;
	updateSelectorPosition();
	return;
}

void HowToPlayMenu::moveSelectorUp()
{
	if (currentSelection == MainMenuSelection::Exit)
	{
		currentSelection = MainMenuSelection::Exit;
		updateSelectorPosition();
		return;
	}

	currentSelection = MainMenuSelection::Exit;
	updateSelectorPosition();
	return;
}
