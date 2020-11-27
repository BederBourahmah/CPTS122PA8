#ifndef SHOP_MODAL_H
#define SHOP_MODAL_H

#include "Modal.h"
#include "TextComponent.h"
#include "MoveableRectangle.h"

/// <summary>
/// This class displays the weapons shop interface.
/// </summary>
class ShopModal : public Modal
{
public:
	ShopModal(sf::VideoMode vm);
	~ShopModal();

	/// <summary>
	/// Draw this component to the provided window.
	/// </summary>
	/// <param name="window">The window to draw to.</param>
	void drawTo(sf::RenderWindow& window);

private:
	/// <summary>
	/// The text component containing the title of the shop.
	/// </summary>
	TextComponent* shopTitle;

	/// <summary>
	/// The text component containing the header for the weapon name column.
	/// </summary>
	TextComponent* weaponNameTableHeader;

	/// <summary>
	/// The text component containing the header for the weapon cost column.
	/// </summary>
	TextComponent* weaponCostTableHeader;

	/// <summary>
	/// The text component containg the header for the weapon description.
	/// </summary>
	TextComponent* weaponDescriptionTableHeader;

	/// <summary>
	/// The text component containing the name of the basic weapon.
	/// </summary>
	TextComponent* basicWeaponName;

	/// <summary>
	/// The text component containing the cost of the basic weapon.
	/// </summary>
	TextComponent* basicWeaponCost;

	/// <summary>
	/// The text component containing the description of the basic weapon.
	/// </summary>
	TextComponent* basicWeaponDescription;

	/// <summary>
	/// The box where the purchase log will be displayed.
	/// </summary>
	MoveableRectangle* purchaseLogBox;

	/// <summary>
	/// The video mode that will render this component.
	/// </summary>
	sf::VideoMode videoMode;
};

#endif // !SHOP_MODAL_H
