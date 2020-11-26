#ifndef TEXT_COMPONENT_H
#define TEXT_COMPONENT_H

#include <SFML/Graphics.hpp>
#include "MoveableComponent.h"

/// <summary>
/// This class inherits MoveableComponent and renders text to the screen.
/// </summary>
class TextComponent : public MoveableComponent
{
public:
	/// <summary>
	/// Initializes the underlying font and the words to be displayed.
	/// </summary>
	/// <param name="textFile">The file name of the font.</param>
	/// <param name="contents">The words to be displayed.</param>
	TextComponent(std::string textFile, std::string contents);

	/// <summary>
	/// Initializes the underlying font and the words to be displayed with a specific size.
	/// </summary>
	/// <param name="textFile">The file name of the font.</param>
	/// <param name="contents">The words to be displayed.</param>
	/// <param name="size">The font size.</param>
	TextComponent(std::string textFile, std::string contents, unsigned int size);

	/// <summary>
	/// Initializes the underlying font and the words to be displayed with a specific size and color.
	/// </summary>
	/// <param name="textFile">The file name of the font.</param>
	/// <param name="contents">The words to be displayed.</param>
	/// <param name="size">The font size.</param>
	/// <param name="color">The font color.</param>
	TextComponent(std::string textFile, std::string contents, unsigned int size, sf::Color color);

	/// <summary>
	/// Returns the x-axis coordinate of the center of this component.
	/// </summary>
	/// <returns>The x-axis coordinate of the center of this component.</returns>
	float getCenterPosX();

	/// <summary>
	/// Returns the y-axis coordinate of the center of this component.
	/// </summary>
	/// <returns>The y-axis coordinate of the center of this component.</returns>
	float getCenterPosY();

	/// <summary>
	/// Return the width of this component in pixels.
	/// </summary>
	/// <returns>The width of this component in pixels.</returns>
	float getWidth();

	/// <summary>
	/// The height of this component in pixels.
	/// </summary>
	/// <returns>The height of this component in pixels.</returns>
	float getHeight();

	/// <summary>
	/// Draws this component to the provided window.
	/// </summary>
	/// <param name="window">The widnow to draw this component to.</param>
	void drawTo(sf::RenderWindow& window);

	/// <summary>
	/// Sets the text to be displayed.
	/// </summary>
	/// <param name="newText">The new text to be displayed.</param>
	void setText(std::string newText);

	/// <summary>
	/// Sets the color of the displayed text.
	/// </summary>
	/// <param name="newColor">The new color for the text.</param>
	void setColor(sf::Color newColor);

private:

	/// <summary>
	/// The underlying text component.
	/// </summary>
	sf::Text text;

	/// <summary>
	/// The underyling font component.
	/// </summary>
	sf::Font font;

	/// <summary>
	/// Updates the position of this component such that it aligns correctly with its current center coordinates.
	/// </summary>
	void updatePosition();
};

#endif // !TEXT_COMPONENT_H
