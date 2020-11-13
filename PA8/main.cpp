#include <SFML/Graphics.hpp>
#include <iostream>
#include "VideoHelpers.h"
#include "MenuSelector.h"
#include "TextComponent.h"
#include "MainMenu.h"

int main()
{
    sf::VideoMode fullscreenVideoMode;
    VideoHelpers::getFullscreenVideoMode(fullscreenVideoMode);
    if (!VideoHelpers::getFullscreenVideoMode(fullscreenVideoMode))
    {
        std::cout << "Failed to get fullscreen video mode." << std::endl;
        return EXIT_FAILURE;
    }

    sf::RenderWindow window(fullscreenVideoMode, "SFML works!", sf::Style::Fullscreen);

    sf::Sprite backgroundSprite;
    if (!VideoHelpers::getMainMenuBackgroundSprite(backgroundSprite, fullscreenVideoMode))
    {
        std::cout << "Failed to load background." << std::endl;
        return EXIT_FAILURE;
    }

    MainMenu mainMenu(fullscreenVideoMode);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            mainMenu.moveSelectorDown();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            mainMenu.moveSelectorUp();
        }

        window.clear();
        window.draw(backgroundSprite);
        mainMenu.draw(window);
        window.display();
    }

    return 0;
}