#include "HowToPlayMenu.h"

HowToPlayMenu::HowToPlayMenu(sf::VideoMode const vm)
{
	videoMode = vm;
	rulesTextHeader = new TextComponent("Leander.ttf", "HOW TO PLAY");
	rulesTextBody = new TextComponent("Leander.ttf", "Ghosts are attacking the castle!\n Click on them to shoot, but\n don't let them get too close!\n");
	returnText = new TextComponent("Leander.ttf", "Return");
	selector = new MenuSelector(returnText->getWidth(), returnText->getHeight());
	rulesTextHeader->centerHorizontal(videoMode);
	rulesTextHeader->snapToVertical(videoMode, 5, 1);
	rulesTextBody->centerHorizontal(videoMode);
	rulesTextBody->snapToVertical(videoMode, 5, 3);
	returnText->centerHorizontal(videoMode);
	returnText->snapToVertical(videoMode, 5, 5);
	if (!loadRulesMenuBackgroundSprite(videoMode))
	{
		std::cout << "Failed to load background sprite." << std::endl;
	}
}

HowToPlayMenu::~HowToPlayMenu()
{
	delete rulesTextHeader;
	rulesTextHeader = nullptr;
	delete rulesTextBody;
	rulesTextBody = nullptr;
	delete returnText;
	returnText = nullptr;
	delete selector;
	selector = nullptr;
}

void HowToPlayMenu::drawTo(sf::RenderWindow& window)
{
	window.draw(backgroundSprite);
	rulesTextHeader->drawTo(window);
	rulesTextBody->drawTo(window);
	returnText->drawTo(window);
	selector->drawTo(window);
}

void HowToPlayMenu::processKeyboardInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		shouldGoBackToMainMenu = true;
	}
}

void HowToPlayMenu::processMousePosition(sf::Vector2i mouseWindowPosition)
{
	if (returnText->isPositionInMyArea(mouseWindowPosition))
	{
		currentSelection = MainMenuSelection::Exit;
		updateSelectorPosition();
		return;
	}
}

void HowToPlayMenu::processMouseClick()
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) return;

	sf::Vector2i mousePosition = sf::Mouse::getPosition();
	if (returnText->isPositionInMyArea(mousePosition))
	{
		currentSelection = MainMenuSelection::Exit; /////
		updateSelectorPosition();
		selectedScreen = Screens::Exit;
		return;
	}
}

bool HowToPlayMenu::shouldExitGame()
{
	return shouldGoBackToMainMenu;
}

void HowToPlayMenu::handleEvents(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
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

void HowToPlayMenu::handleClickEvent(sf::Event event)
{
	if (event.type != sf::Event::MouseButtonReleased || isMenuDisabled() || event.mouseButton.button != sf::Mouse::Left) 
		return;

	sf::Vector2i mousePosition(event.mouseButton.x, event.mouseButton.y);
	if (returnText->isPositionInMyArea(mousePosition))
	{
		shouldGoBackToMainMenu = true;
		currentSelection = MainMenuSelection::SwarmDefender;
		updateSelectorPosition();
		selectedScreen = Screens::MainMenu;
	}
}

bool HowToPlayMenu::isMenuDisabled()
{
	return singVsMultiModal != nullptr || isLoading;
}


void HowToPlayMenu::updateState()
{
	
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
	if (event.type != sf::Event::KeyPressed) 
		return;

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

Screens HowToPlayMenu::getSelectedScreen()
{
	return selectedScreen;
}

void HowToPlayMenu::moveSelectorDown()
{
	currentSelection = MainMenuSelection::Exit;
	updateSelectorPosition();
	return;
}

void HowToPlayMenu::moveSelectorUp()
{
	currentSelection = MainMenuSelection::Exit;
	updateSelectorPosition();
	return;
}

bool HowToPlayMenu::loadRulesMenuBackgroundTexture()
{
	if (!backgroundTexture.loadFromFile("assets/main_menu_background.jpg"))
	{
		return false;
	}
	return true;
}

const static float backgroundWidth = 3071;
const static float backgroundHeight = 2299;

bool HowToPlayMenu::loadRulesMenuBackgroundSprite(sf::VideoMode const videoMode)
{
	if (!loadRulesMenuBackgroundTexture())
	{
		return false;
	}

	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale((float)videoMode.width / backgroundWidth, (float)videoMode.height / backgroundHeight);
	return true;
}
