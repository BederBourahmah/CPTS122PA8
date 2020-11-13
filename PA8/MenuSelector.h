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
	void updatePosition(float posX, float posY);
	void centerHorizontal(sf::VideoMode const videoMode);
	void snapToVertical(sf::VideoMode const videoMode, int sections, int sectionToSnapTo);
	void draw(sf::RenderWindow& window);
private:
	sf::Sprite topLeftSprite;
	sf::Texture topLeftTexture;
	sf::Sprite bottomLeftSprite;
	sf::Texture bottomLeftTexture;
	sf::Sprite topRightSprite;
	sf::Texture topRightTexture;
	sf::Sprite bottomRightSprite;
	sf::Texture bottomRightTexture;
	float getTopPosYToCenter();
	float getLeftPosXToCenter();
	float getBottomPosYToCenter();
	float getRightPosXToCenter();
	float totalWidth;
	float totalHeight;
	float centerPosX;
	float centerPosY;
};

#endif // !MENU_SELECTOR_H
