#include <SFML/Graphics.hpp>
#include <iostream>
#include "VideoHelpers.h"

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
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Sprite backgroundSprite;
    if (!VideoHelpers::getMainMenuBackgroundSprite(backgroundSprite, fullscreenVideoMode))
    {
        std::cout << "Failed to load background." << std::endl;
        return EXIT_FAILURE;
    }

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
        window.draw(shape);
        window.display();
    }

    return 0;
}