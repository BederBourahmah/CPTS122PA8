#ifndef LOADING_MODAL_H
#define LOADING_MODAL_H

#include "Modal.h"

/// <summary>
/// This modal displays a spinning gear to indicate loading.
/// </summary>
class LoadingModal : public Modal
{
public:

	/// <summary>
	/// Initializes the video mode that renders this modal.
	/// </summary>
	/// <param name="vm">The video mode that renders this modal.</param>
	LoadingModal(sf::VideoMode vm);

	~LoadingModal();

	/// <summary>
	/// Draws this modal to the provided window.
	/// </summary>
	/// <param name="window">The window to draw to.</param>
	void drawTo(sf::RenderWindow& window);

	/// <summary>
	/// Updates the internal state of this component.
	/// </summary>
	void updateState();

private:
	/// <summary>
	/// The video mode will render this modal.
	/// </summary>
	sf::VideoMode videoMode;

	/// <summary>
	/// The texture that contains the gear icon.
	/// </summary>
	sf::Texture iconTexture;

	/// <summary>
	/// The rectangle that will contain the rotating gear texture.
	/// </summary>
	sf::RectangleShape gearIcon;

	/// <summary>
	/// A clock to ensure the rotation is time based instead of processor speed based.
	/// </summary>
	sf::Clock rotationClock;

	/// <summary>
	/// The degrees to rotate per millisecond.
	/// </summary>
	const float degreesPerMillisecond = 180.0f / 1000.0f;
};

#endif // !LOADING_MODAL_H
