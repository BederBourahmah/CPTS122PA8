#include "GUIComponent.h"

GUIComponent::GUIComponent()
{
	didLoadSuccessfully = true;
	if (!baseTexture.loadFromFile("assets/gui_components.png"))
	{
		didLoadSuccessfully = false;
	}
}