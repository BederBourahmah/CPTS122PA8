#ifndef GUI_COMPONENT_H
#define GUI_COMPONENT_H

#include <SFML/Graphics.hpp>

class GUIComponent
{
public:
	GUIComponent();

protected:
	sf::Texture baseTexture;
private:
	bool didLoadSuccessfully;
};

#endif // !GUI_COMPONENT_H
