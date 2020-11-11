#include <SFML/Graphics.hpp>
#include <iostream>

const static float backgroundWidth = 3071;
const static float backgroundHeight = 2299;

int main()
{
    std::vector<sf::VideoMode> fullscreenVideoModes = sf::VideoMode::getFullscreenModes();
    if (fullscreenVideoModes.size() < 1)
    {
        std::cout << "Failed to get fullscreen video mode." << std::endl;
        return EXIT_FAILURE;
    }

    sf::VideoMode fullscreenVideoMode = fullscreenVideoModes[0];
    unsigned int fullscreenWidth = fullscreenVideoMode.width;
    unsigned int fullscreenHeight = fullscreenVideoMode.height;
    float screenToBackgroundWidthScale = (float)fullscreenWidth / backgroundWidth;
    float screenToBackgroundHeightScale = (float)fullscreenHeight / backgroundHeight;

    sf::RenderWindow window(fullscreenVideoMode, "SFML works!", sf::Style::Fullscreen);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("brown_age_by_darkwood67.jpg"))
    {
        std::cout << "Failed to load background." << std::endl;
        return EXIT_FAILURE;
    }

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(screenToBackgroundWidthScale, screenToBackgroundHeightScale);

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