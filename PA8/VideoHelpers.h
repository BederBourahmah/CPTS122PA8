#ifndef VIDEO_HELPERS_H
#define VIDEO_HELPERS_H

#include <SFML/Graphics.hpp>

class VideoHelpers
{
public:
	static bool getFullscreenVideoMode(sf::VideoMode &);
	static bool getMainMenuBackgroundSprite(sf::Sprite&, sf::VideoMode const);
private:
	static bool loadMainMenuBackgroundTexture();
	static sf::Texture backgroundTexture;
};

#endif // !VIDEO_HELPERS_H

