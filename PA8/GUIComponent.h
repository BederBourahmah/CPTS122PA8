#ifndef GUI_COMPONENT_H
#define GUI_COMPONENT_H

#include "MoveableComponent.h"
#include <SFML/Graphics.hpp>

class GUIComponent : public MoveableComponent
{
public:
	GUIComponent();

protected:
	sf::Texture baseTexture;
	sf::Texture topDoubleBorder;
	sf::Texture bottomDoubleBorder;
	sf::Texture topLeftDoubleBorder;
	sf::Texture bottomLeftDoubleBorder;
	sf::Texture topRightDoubleBorder;
	sf::Texture bottomRightDoubleBorder;
	sf::Texture leftDoubleBorder;
	sf::Texture rightDoubleBorder;
	sf::Texture modalBackground;

	static const unsigned short cornerDoubleBorderSquareLength = 24;
	static const unsigned short longDoubleBorderThickness = 17;
	static const unsigned short verticalDoubleBorderLength = 55;
	static const unsigned short horizontalDoubleBorderLength = 73;
};

#endif // !GUI_COMPONENT_H
