#include "MainMenu.h"

MainMenu::MainMenu(sf::VideoMode const videoMode)
{
	Start = new TextComponent("Leander.ttf", "Start Game");
	Exit = new TextComponent("Leander.ttf", "Exit Game");
	Selector = new MenuSelector(100, 200);
	Start->centerHorizontal(videoMode);
	Start->move(0, videoMode.height / 2);
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
}
