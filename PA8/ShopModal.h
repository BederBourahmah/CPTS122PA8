#ifndef SHOP_MODAL_H
#define SHOP_MODAL_H

#include "Modal.h"
#include "TextComponent.h"
#include "MoveableRectangle.h"
#include "WeaponType.h"

class SwarmDefense;

/// <summary>
/// This class displays the weapons shop interface.
/// </summary>
class ShopModal : public Modal
{
public:
	ShopModal(
		sf::VideoMode vm,
		SwarmDefense* swarmDefense,
		bool(SwarmDefense::* purchaseWeaponCallback)(unsigned int cost, WeaponType type),
		void(SwarmDefense::* closeModalCallback)()
	);
	~ShopModal();

	/// <summary>
	/// Draw this component to the provided window.
	/// </summary>
	/// <param name="window">The window to draw to.</param>
	void drawTo(sf::RenderWindow& window);

	/// <summary>
	/// Handles the events that have been generated for the window.
	/// </summary>
	/// <param name="window">The window that is generating the events.</param>
	void handleEvents(sf::RenderWindow& window);

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
	/// The text component representing the exit button.
	/// </summary>
	TextComponent* exitButton;

	/// <summary>
	/// The video mode that will render this component.
	/// </summary>
	sf::VideoMode videoMode;

	/// <summary>
	/// A pointer to the parent component.
	/// </summary>
	SwarmDefense* parent;

	/// <summary>
	/// The callback for purchasing a weapon.
	/// </summary>
	bool(SwarmDefense::* onPurchaseWeapon)(unsigned int cost, WeaponType type);

	/// <summary>
	/// The callback for closing this modal.
	/// </summary>
	void(SwarmDefense::* onCloseModal)();

	/// <summary>
	/// Processes a user request to purchase a basic weapon.
	/// </summary>
	void handlePurchaseBasicWeapon();

	/// <summary>
	/// The current cost of the basic weapon.
	/// </summary>
	unsigned int currentBasicWeaponCost;

	/// <summary>
	/// Handles a click event.
	/// </summary>
	/// <param name="event">A click event.</param>
	void handleClickEvent(sf::Event event);
};

#endif // !SHOP_MODAL_H
