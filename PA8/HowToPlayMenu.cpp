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
	
	selector->moveTo(returnText->getCenterPosX(), returnText->getCenterPosY());;
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

void HowToPlayMenu::processMouseClick()
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) return;

	shouldGoBackToMainMenu = true;
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
			shouldGoBackToMainMenu = true;
		}

		if (event.type == sf::Event::MouseButtonReleased)
		{
			shouldGoBackToMainMenu = true;
		}
	}
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

void HowToPlayMenu::processMousePosition(sf::Vector2i mouseWindowPosition)
{

}

void HowToPlayMenu::updateState()
{

}