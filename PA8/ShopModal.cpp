#include "ShopModal.h"

ShopModal::ShopModal(
	sf::VideoMode vm,
	SwarmDefense* swarmDefense,
	bool(SwarmDefense::* purchaseWeaponCallback)(unsigned int cost, WeaponType type),
	void(SwarmDefense::* closeModalCallback)()
) : Modal(ModalSize::ExtraLarge, vm)
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
	weaponDescriptionTableHeader->snapToHorizontal(videoMode, 16, 9);
	weaponDescriptionTableHeader->snapToVertical(videoMode, 16, 5);

	basicWeaponName = new TextComponent("Leander.ttf", "Basic", 30);
	basicWeaponName->snapToHorizontal(videoMode, 16, 4);
	basicWeaponName->snapToVertical(videoMode, 16, 6);

	basicWeaponCost = new TextComponent("Leander.ttf", "10", 30);
	basicWeaponCost->snapToHorizontal(videoMode, 16, 6);
	basicWeaponCost->snapToVertical(videoMode, 16, 6);

	basicWeaponDescription = new TextComponent("Leander.ttf", "Fires 1 projectile per second.", 30);
	basicWeaponDescription->snapToHorizontal(videoMode, 16, 9);
	basicWeaponDescription->snapToVertical(videoMode, 16, 6);

	exitButton = new TextComponent("Leander.ttf", "Exit", 30);
	exitButton->centerHorizontal(videoMode);
	exitButton->snapToVertical(videoMode, 16, 13);

	parent = swarmDefense;
	onPurchaseWeapon = purchaseWeaponCallback;
	onCloseModal = closeModalCallback;
	currentBasicWeaponCost = 10;
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
	delete exitButton;
	exitButton = nullptr;
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
	exitButton->drawTo(window);
}

void ShopModal::handleEvents(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::MouseButtonReleased)
		{
			handleClickEvent(event);
		}

		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
		{
			((*parent).*onCloseModal)();
		}
	}
}

void ShopModal::handlePurchaseBasicWeapon()
{
	if (((*parent).*onPurchaseWeapon)(currentBasicWeaponCost, WeaponType::Basic))
	{
		currentBasicWeaponCost *= 2.0f;
		basicWeaponCost->setText(std::to_string(currentBasicWeaponCost));
		return;
	}

}

void ShopModal::handleClickEvent(sf::Event event)
{
	if (event.type != sf::Event::MouseButtonReleased || event.mouseButton.button != sf::Mouse::Left) return;

	sf::Vector2i mousePosition(event.mouseButton.x, event.mouseButton.y);
	if (basicWeaponName->isPositionInMyArea(mousePosition))
	{
		handlePurchaseBasicWeapon();
		return;
	}

	if (exitButton->isPositionInMyArea(mousePosition))
	{
		((*parent).*onCloseModal)();
		return;
	}
}
