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
	void centerHorizontal(sf::VideoMode const videoMode);
	void snapToVertical(sf::VideoMode const videoMode, int sections, int sectionToSnapTo);
private:
	sf::Text text;
	sf::Font font;
	bool didLoadSuccessfully;
};

#endif // !TEXT_COMPONENT_H
