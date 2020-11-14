#include <SFML/Graphics.hpp>
#include <iostream>
#include "VideoHelpers.h"
#include "MenuSelector.h"
#include "TextComponent.h"
#include "MainMenu.h"

int main()
{
    sf::VideoMode fullscreenVideoMode;
    if (!VideoHelpers::getFullscreenVideoMode(fullscreenVideoMode))
    {
        std::cout << "Failed to get fullscreen video mode." << std::endl;
        return EXIT_FAILURE;
    }

    sf::RenderWindow window(fullscreenVideoMode, "PA8", sf::Style::Fullscreen);
    //Test
    MainMenu mainMenu(fullscreenVideoMode);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        mainMenu.processKeyboardInput();
        mainMenu.processMousePosition(sf::Mouse::getPosition());
        mainMenu.processMouseClick();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || mainMenu.shouldExitGame())
        {
            window.close();
        }

        window.clear();
        mainMenu.drawTo(window);
        window.display();
    }

    return EXIT_SUCCESS;
}