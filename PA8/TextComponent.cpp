#include "TextComponent.h"
#include <iostream>

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
	text.setCharacterSize(100);
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

void TextComponent::centerHorizontal(sf::VideoMode const videoMode)
{
	float textCenterOffset = text.getGlobalBounds().width / 2;
	float videoCenter = videoMode.width / 2;
	float horizontalPos = videoCenter - textCenterOffset;
	text.setPosition(horizontalPos, text.getPosition().y);
}

void TextComponent::snapToVertical(sf::VideoMode const videoMode, int sections, int sectionToSnapTo)
{
	float sizePerSection = (float)videoMode.height / (float)sections;
	float bottomOfSelectedSection = sectionToSnapTo * sizePerSection;
	float topOfSelectedSection = (sectionToSnapTo - 1) * sizePerSection;
	float centerOfSelectedSection = (bottomOfSelectedSection + topOfSelectedSection) / 2;
	float textCenterOffset = text.getGlobalBounds().height / 2;
	float verticalPos = centerOfSelectedSection - textCenterOffset;
	text.setPosition(text.getPosition().x, verticalPos);
}
