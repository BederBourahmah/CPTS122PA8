#ifndef TEXT_COMPONENT_H
#define TEXT_COMPONENT_H

#include <SFML/Graphics.hpp>

class TextComponent
{
public:
	TextComponent();
	TextComponent(std::string, std::string);
	sf::Text getText();
	TextComponent(const TextComponent&);
	sf::Text text;
	void move(float offsetX, float offsetY);
	void centerHorizontal(sf::VideoMode const videoMode);
private:
	sf::Font font;
	bool didLoadSuccessfully;
};

#endif // !TEXT_COMPONENT_H
