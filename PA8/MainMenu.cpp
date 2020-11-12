#include "MainMenu.h"

MainMenu::MainMenu(sf::VideoMode const videoMode)
{
	Start = new TextComponent("Leander.ttf", "Start Game");
	Exit = new TextComponent("Leander.ttf", "Exit Game");
	Selector = new MenuSelector(100, 200);
	Start->centerHorizontal(videoMode);
	Start->snapToVertical(videoMode, 4, 2);
	Exit->centerHorizontal(videoMode);
	Exit->snapToVertical(videoMode, 4, 3);
}

MainMenu::~MainMenu()
{
	delete Start;
	delete Exit;
	delete Selector;
}

void MainMenu::draw(sf::RenderWindow &window)
{
	window.draw(Start->getText());
	window.draw(Exit->getText());
}
