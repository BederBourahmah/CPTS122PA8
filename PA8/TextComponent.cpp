#include "TextComponent.h"

TextComponent::TextComponent(std::string textFile, std::string contents)
{
	didLoadSuccessfully = true;
	if (font.loadFromFile("assets/" + textFile))
	{
		didLoadSuccessfully = false;
	}

	text.setFont(font);
	text.setString(contents);
}

sf::Text TextComponent::getText()
{
	return text;
}