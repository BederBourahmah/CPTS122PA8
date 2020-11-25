#ifndef GUI_COMPONENT_H
#define GUI_COMPONENT_H

#include "MoveableComponent.h"
#include <SFML/Graphics.hpp>

/// <summary>
/// A base class used to inherit textures.
/// </summary>
class GUIComponent : public MoveableComponent
{
public:
	/// <summary>
	/// Loads all textures.
	/// </summary>
	GUIComponent();

protected:
	/// <summary>
	/// The base texture that contains all GUI textures.
	/// </summary>
	sf::Texture baseTexture;

	/// <summary>
	/// The texture for the top double line border.
	/// </summary>
	sf::Texture topDoubleBorder;

	/// <summary>
	/// The texture for the bottom double line border.
	/// </summary>
	sf::Texture bottomDoubleBorder;

	/// <summary>
	/// The texture for the top left corner double line border.
	/// </summary>
	sf::Texture topLeftDoubleBorder;

	/// <summary>
	/// The texture for the bottom left corner double line border.
	/// </summary>
	sf::Texture bottomLeftDoubleBorder;

	/// <summary>
	/// The texture for the top right corner double line border.
	/// </summary>
	sf::Texture topRightDoubleBorder;

	/// <summary>
	/// The texture for the bottom right corner double line border.
	/// </summary>
	sf::Texture bottomRightDoubleBorder;

	/// <summary>
	/// The texture for the left double line border.
	/// </summary>
	sf::Texture leftDoubleBorder;

	/// <summary>
	/// The texture for the right double line border.
	/// </summary>
	sf::Texture rightDoubleBorder;

	/// <summary>
	/// The texture for the modal background.
	/// </summary>
	sf::Texture modalBackground;

	/// <summary>
	/// The texture for the top left corner single line border.
	/// </summary>
	sf::Texture topLeftSingleBorder;

	/// <summary>
	/// The texture for the bottom left corner single line border.
	/// </summary>
	sf::Texture bottomLeftSingleBorder;

	/// <summary>
	/// The texture for the top right corner single line border.
	/// </summary>
	sf::Texture topRightSingleBorder;

	/// <summary>
	/// The texture for the bottom right single line border.
	/// </summary>
	sf::Texture bottomRightSingleBorder;

	/// <summary>
	/// Constant representing the length of each side of the square that makes up the texture of a corner double line border in pixels.
	/// </summary>
	static const unsigned short cornerDoubleBorderSquareLength = 24;

	/// <summary>
	/// Constant representing the thickness of a long double border texture in pixels.
	/// </summary>
	static const unsigned short longDoubleBorderThickness = 17;

	/// <summary>
	/// Constant representing the length of the long vertical double line border in pixels.
	/// </summary>
	static const unsigned short verticalDoubleBorderLength = 55;

	/// <summary>
	/// Constant representing the length of the long horizontal double line border in pixels.
	/// </summary>
	static const unsigned short horizontalDoubleBorderLength = 73;

	/// <summary>
	/// Constant representing the length of each side of the square that makes up the texture of a corner single line border in pixels.
	/// </summary>
	static const int cornerSingleBorderSquareLength = 19;
};

#endif // !GUI_COMPONENT_H
