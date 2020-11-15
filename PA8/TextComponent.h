#ifndef TEXT_COMPONENT_H
#define TEXT_COMPONENT_H

#include <SFML/Graphics.hpp>
#include "MoveableComponent.h"

class TextComponent : public MoveableComponent
{
public:
	TextComponent(std::string textFile, std::string contents);
	TextComponent(std::string textFile, std::string contents, unsigned int size);

	float getCenterPosX();
	float getCenterPosY();
	float getWidth();
	float getHeight();
	void drawTo(sf::RenderWindow& window);
	void setText(std::string newText);
	void setColor(sf::Color newColor);
private:
	sf::Text text;
	sf::Font font;
	void updatePosition();
};

#endif // !TEXT_COMPONENT_H
