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

void TextComponent::centerHorizontal(sf::VideoMode const videoMode)
{
	centerPosX = videoMode.width / 2;
	updatePosition();
}

void TextComponent::snapToVertical(sf::VideoMode const videoMode, int sections, int sectionToSnapTo)
{
	float sizePerSection = (float)videoMode.height / (float)sections;
	float bottomOfSelectedSection = sectionToSnapTo * sizePerSection;
	float topOfSelectedSection = (sectionToSnapTo - 1) * sizePerSection;
	float centerOfSelectedSection = (bottomOfSelectedSection + topOfSelectedSection) / 2;
	float textCenterOffset = text.getGlobalBounds().height / 2;
	float verticalPos = centerOfSelectedSection - textCenterOffset;
	centerPosY = centerOfSelectedSection;
	updatePosition();
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
