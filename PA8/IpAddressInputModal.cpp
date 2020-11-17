#include "IpAddressInputModal.h"

IpAddressInputModal::IpAddressInputModal(sf::VideoMode vm) : Modal(ModalSize::Medium, vm)
{
	videoMode = vm;
	title = new TextComponent("Leander.ttf", "Input IP Address and Port", 18);
	title->centerHorizontal(videoMode);
	title->snapToVertical(videoMode, 8, 2);
	ipAddressTitle = new TextComponent("Leander.ttf", "IP Address and Port", 16);
	ipAddressTitle->centerHorizontal(videoMode);
	ipAddressTitle->snapToVertical(videoMode, 8, 3);
	ipAddressInput = new TextComponent("Leander.ttf", "", 16, sf::Color::Green);
	ipAddressInput->centerHorizontal(videoMode);
	ipAddressInput->snapToVertical(videoMode, 8, 4);
	ipInputBox = new MoveableRectangle(sf::Vector2f(0.2f * videoMode.width, 50), sf::Color::Black);
	ipInputBox->centerHorizontal(videoMode);
	ipInputBox->snapToVertical(videoMode, 8, 4);
}

IpAddressInputModal::~IpAddressInputModal()
{
	delete title;
	title = nullptr;
	delete ipAddressTitle;
	ipAddressTitle = nullptr;
	delete ipAddressInput;
	ipAddressInput = nullptr;
	delete ipInputBox;
	ipInputBox = nullptr;
}

void IpAddressInputModal::drawTo(sf::RenderWindow& window)
{
	Modal::drawTo(window);
	title->drawTo(window);
	ipAddressTitle->drawTo(window);
	ipAddressInput->centerHorizontal(videoMode);
	ipInputBox->drawTo(window);
	ipAddressInput->drawTo(window);

}

void IpAddressInputModal::updateState()
{
	ipAddressInput->setText(currentIpAddress);
}

void IpAddressInputModal::handleEvents(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) window.close();

		if (event.type == sf::Event::TextEntered) handleTextEnteredEvent(event.text.unicode);
	}
}

void IpAddressInputModal::handleTextEnteredEvent(sf::Uint32 enteredChar)
{
	if (enteredChar >= 128) return;

	if (enteredChar == 8)
	{
		handleBackSpace();
		return;
	}

	handleAddText((char)enteredChar);
}

void IpAddressInputModal::handleBackSpace()
{
	if (currentIpAddress.empty()) return;
	
	currentIpAddress.pop_back();
}

void IpAddressInputModal::handleAddText(char charToAdd)
{
	currentIpAddress.push_back(charToAdd);
}
