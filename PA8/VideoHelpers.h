#ifndef VIDEO_HELPERS_H
#define VIDEO_HELPERS_H

#include <SFML/Graphics.hpp>

/// <summary>
/// Helper class with static functions for loading video mode.
/// </summary>
class VideoHelpers
{
public:
	/// <summary>
	/// Loads the best full screen video mode available. If none are available, will return false.
	/// </summary>
	/// <param name="rtnVideoMode">The video mode variable that it will set with the full screen video mode.</param>
	/// <returns>True if loaded successfully, false otherwise.</returns>
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

