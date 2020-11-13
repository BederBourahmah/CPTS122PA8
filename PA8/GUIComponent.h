#ifndef GUI_COMPONENT_H
#define GUI_COMPONENT_H

#include "MoveableComponent.h"
#include <SFML/Graphics.hpp>

class GUIComponent : MoveableComponent
{
public:
	GUIComponent();

protected:
	sf::Texture baseTexture;
};

#endif // !GUI_COMPONENT_H
