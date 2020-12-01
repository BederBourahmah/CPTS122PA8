#ifndef MOVEABLE_RECTANGLE_H
#define MOVEABLE_RECTANGLE_H

#include "MoveableComponent.h"
#include <SFML/Graphics.hpp>
#include <iostream>

/// <summary>
/// This class inherits the MoveableComponent class and extends it.
/// </summary>
class MoveableRectangle : public MoveableComponent
{
public:
	/// <summary>
	/// Initializes only the dimensions of this component.
	/// </summary>
	/// <param name="dimensions">The dimensions of this component.</param>
	MoveableRectangle(sf::Vector2f dimensions);

	/// <summary>
	/// Initializes the dimensions and the color of this component.
	/// </summary>
	/// <param name="dimensions">The dimensions of this component.</param>
	/// <param name="color">The color of this component.</param>
	MoveableRectangle(sf::Vector2f dimensions, sf::Color color);

	/// <summary>
	/// Initializes the dimensions and the texture of this component.
	/// </summary>
	/// <param name="dimensions">The dimensions of this component.</param>
	/// <param name="txtr">The texture of this component.</param>
	MoveableRectangle(sf::Vector2f dimensions, const sf::Texture* txtr);

	/// <summary>
	/// Draws this component to the provided window.
	/// </summary>
	/// <param name="window">The window to draw this component to.</param>
	void drawTo(sf::RenderWindow& window);

	/// <summary>
	/// Returns true if this component collided with the provided component.
	/// </summary>
	/// <param name="otherComponent">The component to check if this component has collided with.</param>
	/// <returns>True if this component collided with the provided component.</returns>
	bool didCollideWithOtherComponent(MoveableRectangle otherComponent);

	/// <summary>
	/// Sets the texture of this component. Used mostly for animation.
	/// </summary>
	/// <param name="newTexture">The new texture this component will render.</param>
	void setTexture(const sf::Texture* newTexture);

	/// <summary>
	/// Mirrors this component along the y-axis. Used when texture is not symmetrical along the y-axis.
	/// </summary>
	void mirror();

	/// <summary>
	/// Returs true if this component is left of the center axis.
	/// </summary>
	/// <param name="center">The x-axis coordinate of the center.</param>
	/// <returns>True if this component is left of the center axis.</returns>
	bool isLeftOfCenter(float center);

protected:
	/// <summary>
	/// Updates the dimensions of this component. Mostly used for animation to account for different sprite sizes.
	/// </summary>
	/// <param name="dimensions"></param>
	/// <param name="originOffset"></param>
	void updateDimensions(sf::Vector2f dimensions, sf::Vector2f originOffset);

private:
	/// <summary>
	/// The base shape for this component.
	/// </summary>
	sf::RectangleShape shape;

	/// <summary>
	/// Updates the position of this component so it is correctly positioned relative to the center.
	/// </summary>
	void updatePosition();

	/// <summary>
	/// Returns true if the two components collided.
	/// </summary>
	/// <param name="componentA">The first component in the potential collision.</param>
	/// <param name="componentB">The other component in the potential collision.</param>
	/// <returns>True if the two components collided.</returns>
	static bool didComponentsCollide(MoveableRectangle componentA, MoveableRectangle componentB)
	{
		return doOverlapOnX(componentA, componentB) && doOverlapOnY(componentA, componentB);
	}

	/// <summary>
	/// Returns true if the two components overlap on the x-axis.
	/// </summary>
	/// <param name="componentA">The first component in the potential collision.</param>
	/// <param name="componentB">The other component in the potential collision.</param>
	/// <returns></returns>
	static bool doOverlapOnX(MoveableRectangle componentA, MoveableRectangle componentB)
	{
		return componentA.getRightPosXToCenter() >= componentB.getLeftPosXToCenter() && componentA.getLeftPosXToCenter() <= componentB.getRightPosXToCenter();
	}

	/// <summary>
	/// Returns true if the two components overlap on the y-axis.
	/// </summary>
	/// <param name="componentA">The first component in the potential collision.</param>
	/// <param name="componentB">The other component in the potential collision.</param>
	/// <returns></returns>
	static bool doOverlapOnY(MoveableRectangle componentA, MoveableRectangle componentB)
	{
		return componentA.getBottomPosYToCenter() >= componentB.getTopPosYToCenter() && componentA.getTopPosYToCenter() <= componentB.getBottomPosYToCenter();
	}
};

#endif // !MOVEABLE_RECTANGLE_H
