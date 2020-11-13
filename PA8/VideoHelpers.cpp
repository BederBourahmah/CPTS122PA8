#include "VideoHelpers.h"

bool VideoHelpers::getFullscreenVideoMode(sf::VideoMode &rtnVideoMode)
{
    std::vector<sf::VideoMode> fullscreenVideoModes = sf::VideoMode::getFullscreenModes();

    if (fullscreenVideoModes.size() < 1) return false;

    rtnVideoMode = fullscreenVideoModes[0];
    return true;
}