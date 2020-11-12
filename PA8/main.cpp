#include <SFML/Graphics.hpp>
#include <iostream>
#include "VideoHelpers.h"
#include "MenuSelector.h"
#include "TextComponent.h"

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

    MenuSelector menuSelector(100, 100);

    sf::Sprite backgroundSprite;
    if (!VideoHelpers::getMainMenuBackgroundSprite(backgroundSprite, fullscreenVideoMode))
    {
        std::cout << "Failed to load background." << std::endl;
        return EXIT_FAILURE;
    }

    TextComponent testText("Leander.ttf", "Test string");

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

        window.clear();
        window.draw(backgroundSprite);
        window.draw(menuSelector.getTopLeftSprite());
        window.draw(menuSelector.getBottomLeftSprite());
        window.draw(menuSelector.getBottomRightSprite());
        window.draw(menuSelector.getTopRightSprite());
        window.draw(testText.getText());
        window.display();
    }

    return 0;
}