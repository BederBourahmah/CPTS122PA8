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
	totalHeight = text.getGlobalBounds().height;
	totalWidth = text.getGlobalBounds().width;
	centerPosX = totalWidth / 2;
	centerPosY = totalHeight / 2;
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

void TextComponent::updatePosition()
{
	text.setPosition(centerPosX, centerPosY);
}
