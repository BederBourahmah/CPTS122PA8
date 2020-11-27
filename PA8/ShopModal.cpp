#include "ShopModal.h"

ShopModal::ShopModal(sf::VideoMode vm) : Modal(ModalSize::ExtraLarge, vm)
{
	videoMode = vm;

	shopTitle = new TextComponent("Leander.ttf", "Weapons Shop", 30);
	shopTitle->centerHorizontal(videoMode);
	shopTitle->snapToVertical(videoMode, 16, 4);

	weaponNameTableHeader = new TextComponent("Leander.ttf", "Type", 30);
	weaponNameTableHeader->snapToHorizontal(videoMode, 16, 4);
	weaponNameTableHeader->snapToVertical(videoMode, 16, 5);

	weaponCostTableHeader = new TextComponent("Leander.ttf", "Cost", 30);
	weaponCostTableHeader->snapToHorizontal(videoMode, 16, 6);
	weaponCostTableHeader->snapToVertical(videoMode, 16, 5);

	weaponDescriptionTableHeader = new TextComponent("Leander.ttf", "Description", 30);
	weaponDescriptionTableHeader->snapToHorizontal(videoMode, 16, 10);
	weaponDescriptionTableHeader->snapToVertical(videoMode, 16, 5);

	basicWeaponName = new TextComponent("Leander.ttf", "Basic", 30);
	basicWeaponName->snapToHorizontal(videoMode, 16, 4);
	basicWeaponName->snapToVertical(videoMode, 16, 6);

	basicWeaponCost = new TextComponent("Leander.ttf", "10", 30);
	basicWeaponCost->snapToHorizontal(videoMode, 16, 6);
	basicWeaponCost->snapToVertical(videoMode, 16, 6);

	basicWeaponDescription = new TextComponent("Leander.ttf", "Fires 1 projectile per second.", 30);
	basicWeaponDescription->snapToHorizontal(videoMode, 16, 10);
	basicWeaponDescription->snapToVertical(videoMode, 16, 6);

	purchaseLogBox = new MoveableRectangle(sf::Vector2f(0.70f * videoMode.width, 0.1875f * videoMode.height), sf::Color::Black);
	purchaseLogBox->centerHorizontal(videoMode);
	purchaseLogBox->snapToVertical(videoMode, 16, 12);
}

ShopModal::~ShopModal()
{
	delete shopTitle;
	shopTitle = nullptr;
	delete weaponNameTableHeader;
	weaponNameTableHeader = nullptr;
	delete basicWeaponName;
	basicWeaponName = nullptr;
	delete weaponCostTableHeader;
	weaponCostTableHeader = nullptr;
	delete weaponDescriptionTableHeader;
	weaponDescriptionTableHeader = nullptr;
	delete basicWeaponCost;
	basicWeaponCost = nullptr;
	delete basicWeaponDescription;
	basicWeaponDescription = nullptr;
	delete purchaseLogBox;
	purchaseLogBox = nullptr;
}

void ShopModal::drawTo(sf::RenderWindow& window)
{
	Modal::drawTo(window);
	shopTitle->drawTo(window);
	weaponNameTableHeader->drawTo(window);
	weaponCostTableHeader->drawTo(window);
	basicWeaponName->drawTo(window);
	weaponDescriptionTableHeader->drawTo(window);
	basicWeaponCost->drawTo(window);
	basicWeaponDescription->drawTo(window);
	purchaseLogBox->drawTo(window);
}
