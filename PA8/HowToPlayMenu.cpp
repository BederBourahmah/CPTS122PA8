#include "HowToPlayMenu.h"

HowToPlayMenu::HowToPlayMenu(sf::VideoMode const vm)
{
	videoMode = vm;
	rulesTextHeader = new TextComponent("Leander.ttf", "HOW TO PLAY", 100);
	rulesTextBody = new TextComponent("Leander.ttf", "Ghosts are attacking the castle!\nClick on them to shoot, but do\nnot let them get too close! Buy\nweapons from the shop to\nincrease your defense!\n\nControls:\nLeft Mouse Button ~ Shoot\nEsc ~ Exit Game\nS ~ Weapons Shop", 75);
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

void HowToPlayMenu::resetState()
{
	shouldGoBackToMainMenu = false;
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