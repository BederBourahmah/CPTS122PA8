#ifndef TEXT_COMPONENT_H
#define TEXT_COMPONENT_H

#include <SFML/Graphics.hpp>
#include "MoveableComponent.h"

class TextComponent : public MoveableComponent
{
public:
	TextComponent(std::string textFile, std::string contents);

	float getCenterPosX();
	float getCenterPosY();
	float getWidth();
	float getHeight();
	void drawTo(sf::RenderWindow& window);
	bool isPositionInMyArea(sf::Vector2i position);
private:
	sf::Text text;
	sf::Font font;
	void updatePosition();
};

#endif // !TEXT_COMPONENT_H
