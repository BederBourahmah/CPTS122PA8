#include "TextComponent.h"

TextComponent::TextComponent()
{
	didLoadSuccessfully = false;
}

TextComponent::TextComponent(std::string textFile, std::string contents)
{
	didLoadSuccessfully = true;
	if (font.loadFromFile("assets/" + textFile))
	{
		didLoadSuccessfully = false;
	}

	text.setFont(font);
	text.setString(contents);
	text.setFillColor(sf::Color::Black);
}

sf::Text TextComponent::getText()
{
	return text;
}

TextComponent::TextComponent(const TextComponent& compToCopy)
{
	font = compToCopy.font;
	didLoadSuccessfully = compToCopy.didLoadSuccessfully;
	text = compToCopy.text;
}

void TextComponent::move(float offsetX, float offsetY)
{
	text.move(offsetX, offsetY);
}

void TextComponent::centerHorizontal(sf::VideoMode const videoMode)
{
	sf::FloatRect textBounds = text.getGlobalBounds();
	float textWidth = textBounds.width;
	move((float)(videoMode.width - textWidth)/2, 0);
}
