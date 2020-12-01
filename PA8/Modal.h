#ifndef MODAL_H
#define MODAL_H

#include "ModalSize.h"
#include <SFML/Graphics.hpp>
#include "ModalBorder.h"
#include "GUIComponent.h"

/// <summary>
/// The generic modal component.
/// </summary>
class Modal : public GUIComponent
{
public:
	/// <summary>
	/// Initializes the modal with the appropriate size and textures.
	/// </summary>
	/// <param name="s">The size of the modal.</param>
	/// <param name="vm">The video mode that will render this component.</param>
	Modal(ModalSize s, sf::VideoMode vm);

	~Modal();

	/// <summary>
	/// Draw this component to the provided window.
	/// </summary>
	/// <param name="window">The window to draw to.</param>
	void drawTo(sf::RenderWindow& window);

private:
	/// <summary>
	/// Update the position of this modal to align with its center point.
	/// </summary>
	void updatePosition();

	/// <summary>
	/// Loads the background for the modal.
	/// </summary>
	/// <returns>True if the background loaded successfully.</returns>
	bool loadModalBackground();

	/// <summary>
	/// The rectangle representing the background which will render the background texture.
	/// </summary>
	sf::RectangleShape background;

	/// <summary>
	/// The video mode that will render this modal.
	/// </summary>
	sf::VideoMode videoMode;

	/// <summary>
	/// Returns the width of this modal in pixels.
	/// </summary>
	/// <returns>The width of this component in pixels.</returns>
	float getWidthByModalSize();

	/// <summary>
	/// Returns the height of this component in pixels.
	/// </summary>
	/// <returns>The height of this component in pixels.</returns>
	float getHeightByModalSize();

	/// <summary>
	/// Gets the position of halfway through the leftside border. Used to position the background so it doesn't overflow.
	/// </summary>
	/// <returns>The position of halfway through the leftside border.</returns>
	float getInnerLeftFromCenter();

	/// <summary>
	/// Gets the position of halfway through the top border. Used to position the background so it doesn't overflow.
	/// </summary>
	/// <returns>The position of halfway through the top border.</returns>
	float getInnerTopFromCenter();

	/// <summary>
	/// The size of the modal.
	/// </summary>
	ModalSize size;

	/// <summary>
	/// A pointer to the modal border object.
	/// </summary>
	ModalBorder* border;
};

#endif // !MODAL_H
