#ifndef MODAL_BORDER_H
#define MODAL_BORDER_H

#include "GUIComponent.h"
#include <SFML/Graphics.hpp>

/// <summary>
/// This class contains the rectangle shapes used as the modal border.
/// </summary>
class ModalBorder : public GUIComponent
{
public:
	/// <summary>
	/// Initializes all the rectangle shapes with their appropriate textures.
	/// </summary>
	/// <param name="width">The width in pixels of the modal that this border will be applied to.</param>
	/// <param name="height">The height in pixels of the modal that this border will be applied to.</param>
	ModalBorder(float width, float height);

	/// <summary>
	/// Updates the position of the border so all shapes that make up this modal are correctly positioned around the center point.
	/// </summary>
	void updatePosition();

	/// <summary>
	/// Draws this component to the provided window.
	/// </summary>
	/// <param name="window">The window to which this component will be drawn.</param>
	void drawTo(sf::RenderWindow& window);

private:
	/// <summary>
	/// The shape containing the texture for the top left border.
	/// </summary>
	sf::RectangleShape topLeftBorder;

	/// <summary>
	/// The shape containing the texture for the bottom left border.
	/// </summary>
	sf::RectangleShape bottomLeftBorder;

	/// <summary>
	/// The shape containing the texture for the top right border.
	/// </summary>
	sf::RectangleShape topRightBorder;

	/// <summary>
	/// The shape containing the texture for the bottom right border.
	/// </summary>
	sf::RectangleShape bottomRightBorder;

	/// <summary>
	/// The shape containing the texture for the top border.
	/// </summary>
	sf::RectangleShape topBorder;

	/// <summary>
	/// The shape containing the texture for the bottom border.
	/// </summary>
	sf::RectangleShape bottomBorder;

	/// <summary>
	/// The shape containing the texture for the left border.
	/// </summary>
	sf::RectangleShape leftBorder;

	/// <summary>
	/// The shape containing the texture for the right border.
	/// </summary>
	sf::RectangleShape rightBorder;
};

#endif // !MODAL_BORDER_H
