#include "VideoHelpers.h"

const static float backgroundWidth = 3071;
const static float backgroundHeight = 2299;

sf::Texture VideoHelpers::backgroundTexture;

bool VideoHelpers::getFullscreenVideoMode(sf::VideoMode &rtnVideoMode)
{
    std::vector<sf::VideoMode> fullscreenVideoModes = sf::VideoMode::getFullscreenModes();

    if (fullscreenVideoModes.size() < 1) return false;

    rtnVideoMode = fullscreenVideoModes[0];
    return true;
}

bool VideoHelpers::loadMainMenuBackgroundTexture()
{
    if (!backgroundTexture.loadFromFile("assets/main_menu_background.jpg"))
    {
        return false;
    }
    return true;
}

bool VideoHelpers::getMainMenuBackgroundSprite(sf::Sprite &rtnSprite, sf::VideoMode const videoMode)
{
    if (!loadMainMenuBackgroundTexture())
    {
        return false;
    }

    rtnSprite.setTexture(backgroundTexture);
    rtnSprite.setScale((float)videoMode.width / backgroundWidth, (float)videoMode.height / backgroundHeight);
    return true;
}