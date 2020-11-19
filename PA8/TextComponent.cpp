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

TextComponent::TextComponent(std::string textFile, std::string contents, unsigned int size)
{
	if (!font.loadFromFile("assets/" + textFile))
	{
		std::cout << "Failed to load '" << textFile << "' text file." << std::endl;
	}

	text.setFont(font);
	text.setString(contents);
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(size);
	totalHeight = text.getGlobalBounds().height;
	totalWidth = text.getGlobalBounds().width;
	centerPosX = totalWidth / 2;
	centerPosY = totalHeight / 2;
	text.setOrigin(centerPosX, centerPosY);
}

TextComponent::TextComponent(std::string textFile, std::string contents, unsigned int size, sf::Color color)
{
	if (!font.loadFromFile("assets/" + textFile))
	{
		std::cout << "Failed to load '" << textFile << "' text file." << std::endl;
	}

	text.setFont(font);
	text.setString(contents);
	text.setFillColor(color);
	text.setCharacterSize(size);
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

void TextComponent::setText(std::string newText)
{
	float prevWidth = totalWidth;
	text.setString(newText);
	totalWidth = getWidth();
	text.setOrigin(text.getOrigin().x + ((totalWidth - prevWidth) / 2), 0);
}

void TextComponent::setColor(sf::Color newColor)
{
	text.setFillColor(newColor);
}

void TextComponent::updatePosition()
{
	text.setPosition(centerPosX, centerPosY);
}
