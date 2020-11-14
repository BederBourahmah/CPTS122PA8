#ifndef MENU_SELECTOR_H
#define MENU_SELECTOR_H

#include <SFML/Graphics.hpp>
#include "GUIComponent.h"

class MenuSelector : public GUIComponent
{
public:
	MenuSelector(float width, float height);

	sf::Sprite getTopLeftSprite();
	sf::Sprite getBottomLeftSprite();
	sf::Sprite getTopRightSprite();
	sf::Sprite getBottomRightSprite();
	void updatePosition();
	void drawTo(sf::RenderWindow& window);
private:
	sf::Sprite topLeftSprite;
	sf::Texture topLeftTexture;
	sf::Sprite bottomLeftSprite;
	sf::Texture bottomLeftTexture;
	sf::Sprite topRightSprite;
	sf::Texture topRightTexture;
	sf::Sprite bottomRightSprite;
	sf::Texture bottomRightTexture;
};

#endif // !MENU_SELECTOR_H
