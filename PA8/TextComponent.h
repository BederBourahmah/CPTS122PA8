#ifndef TEXT_COMPONENT_H
#define TEXT_COMPONENT_H

#include <SFML/Graphics.hpp>

class TextComponent
{
public:
	TextComponent(std::string, std::string);
	sf::Text getText();
private:
	sf::Font font;
	bool didLoadSuccessfully;
	sf::Text text;
};

#endif // !TEXT_COMPONENT_H
