#include "Modal.h"

const static float backgroundWidth = 3072;
const static float backgroundHeight = 2304;

Modal::Modal(ModalSize s, sf::VideoMode vm)
{
	videoMode = vm;
	size = s;
	totalHeight = getHeightByModalSize();
	border = new ModalBorder(getWidthByModalSize(), totalHeight);
	loadModalBackground();
	totalWidth = getWidthByModalSize();
	centerPosX = totalWidth / 2;
	centerPosY = totalHeight / 2;
	snapToHorizontal(videoMode, 3, 2);
	snapToVertical(videoMode, 3, 2);
}

Modal::~Modal()
{
	delete border;
	border = nullptr;
}

void Modal::drawTo(sf::RenderWindow& window)
{
	window.draw(background);
	border->drawTo(window);
}

void Modal::updatePosition()
{
	border->moveTo(centerPosX, centerPosY);
	background.setPosition(centerPosX, centerPosY);
}

bool Modal::loadModalBackground()
{
	float modalWidth = getWidthByModalSize() - 17;
	float modalHeight = getHeightByModalSize() - 17;
	background.setTexture(&modalBackground);
	background.setSize(sf::Vector2f(modalWidth, modalHeight));
	background.setOrigin(modalWidth/2, modalHeight/2);
	return true;
}

float Modal::getWidthByModalSize()
{
	switch (size)
	{
	case ModalSize::Small:
		return (float)videoMode.width * 0.125f;
	case ModalSize::Medium:
		return (float)videoMode.width * 0.25f;
	case ModalSize::Large:
		return (float)videoMode.width * 0.5f;
	case ModalSize::ExtraLarge:
	default:
		return (float)videoMode.width * 0.75f;
	}
}

float Modal::getHeightByModalSize()
{
	switch (size)
	{
	case ModalSize::Small:
		return (float)videoMode.height * 0.5f;
	case ModalSize::Medium:
	case ModalSize::Large:
	case ModalSize::ExtraLarge:
	default:
		return (float)videoMode.height * 0.75f;
	}
}

float Modal::getInnerLeftFromCenter()
{
	return (8.5f + centerPosY) - totalWidth / 2;
}

float Modal::getInnerTopFromCenter()
{
	return (8.5f + centerPosX) - totalHeight / 2;
}
