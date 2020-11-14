#ifndef VIDEO_HELPERS_H
#define VIDEO_HELPERS_H

#include <SFML/Graphics.hpp>

class VideoHelpers
{
public:
	static bool getFullscreenVideoMode(sf::VideoMode& rtnVideoMode)
    {
        std::vector<sf::VideoMode> fullscreenVideoModes = sf::VideoMode::getFullscreenModes();

        if (fullscreenVideoModes.size() < 1) return false;

        rtnVideoMode = fullscreenVideoModes[0];
        return true;
    }
private:
};

#endif // !VIDEO_HELPERS_H

