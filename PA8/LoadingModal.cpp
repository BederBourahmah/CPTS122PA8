#include "LoadingModal.h"
#include <iostream>

LoadingModal::LoadingModal(sf::VideoMode vm) : Modal(ModalSize::Small, vm)
{
	videoMode = vm;
	if (!iconTexture.loadFromFile("assets/gear_icon.png"))
	{
		std::cout << "Failed to load gear_icon texture;" << std::endl;
	}

	float iconSize = 0.1f * videoMode.width;
	
	gearIcon.setTexture(&iconTexture);
	gearIcon.setSize(sf::Vector2f(iconSize, iconSize));
	gearIcon.setOrigin(iconSize / 2, iconSize / 2);
	gearIcon.setPosition((float)videoMode.width / 2, (float)videoMode.height / 2);
}

LoadingModal::~LoadingModal()
{
}

void LoadingModal::drawTo(sf::RenderWindow& window)
{
	Modal::drawTo(window);
	window.draw(gearIcon);
}

void LoadingModal::updateState()
{
	float timeElapsed = (float)rotationClock.getElapsedTime().asMilliseconds();
	gearIcon.rotate(timeElapsed * degreesPerMillisecond);
	if (timeElapsed > 0) rotationClock.restart();
}
