#include "GUIComponent.h"
#include <iostream>

GUIComponent::GUIComponent()
{
	if (!baseTexture.loadFromFile("assets/gui_components.png"))
	{
		std::cout << "Failed to load GUI components texture." << std::endl;
	}
}