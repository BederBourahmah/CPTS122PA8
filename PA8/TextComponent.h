#ifndef TEXT_COMPONENT_H
#define TEXT_COMPONENT_H

#include <SFML/Graphics.hpp>
#include "MoveableComponent.h"

class TextComponent : MoveableComponent
{
public:
	TextComponent(std::string textFile, std::string contents);

	void centerHorizontal(sf::VideoMode const videoMode);
	void snapToVertical(sf::VideoMode const videoMode, int sections, int sectionToSnapTo);
	float getCenterPosX();
	float getCenterPosY();
	float getWidth();
	float getHeight();
	void drawTo(sf::RenderWindow& window);
private:
	sf::Text text;
	sf::Font font;
	float centerPosX;
	float centerPosY;
	void updatePosition();
};

#endif // !TEXT_COMPONENT_H
