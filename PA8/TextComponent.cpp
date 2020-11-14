#include "TextComponent.h"
#include <iostream>

TextComponent::TextComponent(std::string textFile, std::string contents)
{
	if (!font.loadFromFile("assets/" + textFile))
	{
		std::cout << "Failed to load '" << textFile << "' text file." << std::endl;
	}

	text.setFont(font);
	text.setString(contents);
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(100);
	centerPosX = text.getGlobalBounds().width / 2;
	centerPosY = text.getGlobalBounds().height / 2;
	text.setOrigin(centerPosX, centerPosY);
}

float TextComponent::getCenterPosX()
{
	return centerPosX;
}

float TextComponent::getCenterPosY()
{
	return centerPosY;
}

float TextComponent::getWidth()
{
	return text.getGlobalBounds().width;
}

float TextComponent::getHeight()
{
	return text.getGlobalBounds().height;
}

void TextComponent::drawTo(sf::RenderWindow& window)
{
	window.draw(text);
}

bool TextComponent::isPositionInMyArea(sf::Vector2i position)
{
	return false;
}

void TextComponent::updatePosition()
{
	text.setPosition(centerPosX, centerPosY);
}
