#include "GUIComponent.h"
#include <iostream>

GUIComponent::GUIComponent()
{
	if (!baseTexture.loadFromFile("assets/gui_components.png"))
	{
		std::cout << "Failed to load GUI components texture." << std::endl;
	}

	if (!topDoubleBorder.loadFromFile("assets/top_double_border.png"))
	{
		std::cout << "Failed to load top_double_border texture." << std::endl;
	}
	topDoubleBorder.setRepeated(true);

	if (!bottomDoubleBorder.loadFromFile("assets/bottom_double_border.png"))
	{
		std::cout << "Failed to load bottom_double_border texture." << std::endl;
	}
	bottomDoubleBorder.setRepeated(true);

	if (!topLeftDoubleBorder.loadFromFile("assets/top_left_double_border.png"))
	{
		std::cout << "Failed to load top_left_double_border texture." << std::endl;
	}

	if (!bottomLeftDoubleBorder.loadFromFile("assets/bottom_left_double_border.png"))
	{
		std::cout << "Failed to load bottom_left_double_border texture." << std::endl;
	}

	if (!topRightDoubleBorder.loadFromFile("assets/top_right_double_border.png"))
	{
		std::cout << "Failed to load top_right_double_border texture." << std::endl;
	}

	if (!bottomRightDoubleBorder.loadFromFile("assets/bottom_right_double_border.png"))
	{
		std::cout << "Failed to load bottom_right_double_border texture." << std::endl;
	}

	if (!leftDoubleBorder.loadFromFile("assets/left_double_border.png"))
	{
		std::cout << "Failed to load left_double_border texture." << std::endl;
	}
	leftDoubleBorder.setRepeated(true);

	if (!rightDoubleBorder.loadFromFile("assets/right_double_border.png"))
	{
		std::cout << "Failed to load right_double_border texture." << std::endl;
	}
	rightDoubleBorder.setRepeated(true);

	if (!modalBackground.loadFromFile("assets/modal_background.jpg"))
	{
		std::cout << "Failed to load modal_background texture." << std::endl;
	}

	if (!topLeftSingleBorder.loadFromFile("assets/top_left_single_border.png"))
	{
		std::cout << "Failed to load top_left_single_border texture." << std::endl;
	}

	if (!bottomLeftSingleBorder.loadFromFile("assets/bottom_left_single_border.png"))
	{
		std::cout << "Failed to load bottom_left_single_border texture." << std::endl;
	}

	if (!topRightSingleBorder.loadFromFile("assets/top_right_single_border.png"))
	{
		std::cout << "Failed to load top_right_single_border texture." << std::endl;
	}

	if (!bottomRightSingleBorder.loadFromFile("assets/bottom_right_single_border.png"))
	{
		std::cout << "Failed to load bottom_right_single_border texture." << std::endl;
	}
}