#ifndef MENU_SELECTOR_H
#define MENU_SELECTOR_H

#include <SFML/Graphics.hpp>
#include "GUIComponent.h"

/// <summary>
/// The component that highlights buttons in a menu.
/// </summary>
class MenuSelector : public GUIComponent
{
public:
	/// <summary>
	/// Initializes all the textures, widths, and heights.
	/// </summary>
	/// <param name="width">The width in pixels.</param>
	/// <param name="height">The width in pixels.</param>
	MenuSelector(float width, float height);

	/// <summary>
	/// Update the position of the menu selector to match current center.
	/// </summary>
	void updatePosition();

	/// <summary>
	/// Draws this component to the window.
	/// </summary>
	/// <param name="window">The window to draw to.</param>
	void drawTo(sf::RenderWindow& window);

private:
	/// <summary>
	/// The rectangle shape representing the top left corner.
	/// </summary>
	sf::RectangleShape topLeftBorder;

	/// <summary>
	/// The rectangle shape representing the bottom left corner.
	/// </summary>
	sf::RectangleShape bottomLeftBorder;

	/// <summary>
	/// The rectangle shape representing the top right corner.
	/// </summary>
	sf::RectangleShape topRightBorder;

	/// <summary>
	/// The rectangle shape representing the bottom right corner.
	/// </summary>
	sf::RectangleShape bottomRightBorder;
};

#endif // !MENU_SELECTOR_H
