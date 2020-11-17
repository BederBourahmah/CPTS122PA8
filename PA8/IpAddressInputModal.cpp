#include "IpAddressInputModal.h"

IpAddressInputModal::IpAddressInputModal(sf::VideoMode vm) : Modal(ModalSize::Medium, vm)
{
	videoMode = vm;
	title = new TextComponent("Leander.ttf", "Input IP Address and Port", 20);
	title->centerHorizontal(videoMode);
	title->snapToVertical(videoMode, 8, 2)
		;
	ipAddressTitle = new TextComponent("Leander.ttf", "IP Address", 18);
	ipAddressTitle->centerHorizontal(videoMode);
	ipAddressTitle->snapToVertical(videoMode, 8, 3);

	ipAddressInput = new TextComponent("Leander.ttf", "", 18, sf::Color::Green);
	ipAddressInput->centerHorizontal(videoMode);
	ipAddressInput->snapToVertical(videoMode, 8, 4);

	float boxHeight = (50.0f / 1080.0f)*videoMode.height;
	ipInputBox = new MoveableRectangle(sf::Vector2f(0.2f * videoMode.width, boxHeight), sf::Color::Black);
	ipInputBox->centerHorizontal(videoMode);
	ipInputBox->snapToVertical(videoMode, 8, 4);

	portTitle = new TextComponent("Leander.ttf", "Port", 18);
	portTitle->centerHorizontal(videoMode);
	portTitle->snapToVertical(videoMode, 8, 5);

	portInput = new TextComponent("Leander.ttf", "", 18, sf::Color::Green);
	portInput->centerHorizontal(videoMode);
	portInput->snapToVertical(videoMode, 8, 6);

	portInputBox = new MoveableRectangle(sf::Vector2f(0.2f * videoMode.width, boxHeight), sf::Color::Black);
	portInputBox->centerHorizontal(videoMode);
	portInputBox->snapToVertical(videoMode, 8, 6);

	boxHighlighter = new MoveableRectangle(sf::Vector2f(0.2f * videoMode.width + 5, boxHeight+5), sf::Color::Red);
	boxHighlighter->centerHorizontal(videoMode);
	boxHighlighter->snapToVertical(videoMode, 8, 4);
	isIpInputSelected = true;
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
	delete portTitle;
	portTitle = nullptr;
	delete portInput;
	portInput = nullptr;
	delete boxHighlighter;
	boxHighlighter = nullptr;
}

void IpAddressInputModal::drawTo(sf::RenderWindow& window)
{
	Modal::drawTo(window);
	title->drawTo(window);
	ipAddressTitle->drawTo(window);
	ipAddressInput->centerHorizontal(videoMode);
	boxHighlighter->drawTo(window);
	ipInputBox->drawTo(window);
	ipAddressInput->drawTo(window);
	portTitle->drawTo(window);
	portInputBox->drawTo(window);
	portInput->drawTo(window);
}

void IpAddressInputModal::updateState()
{
	ipAddressInput->setText(currentIpAddress);
	portInput->setText(currentPort);
}

void IpAddressInputModal::processMouseClick(sf::Vector2i mousePosition)
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) return;

	if (portInputBox->isPositionInMyArea(mousePosition))
	{
		boxHighlighter->snapToVertical(videoMode, 8, 6);
		isIpInputSelected = false;
		return;
	}

	if (ipInputBox->isPositionInMyArea(mousePosition))
	{
		boxHighlighter->snapToVertical(videoMode, 8, 4);
		isIpInputSelected = true;
		return;
	}
}

void IpAddressInputModal::handleEvents(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
			continue;
		}
		if (event.type == sf::Event::TextEntered)
		{
			handleTextEnteredEvent(event.text.unicode);
			continue;
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				processMouseClick(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			}
			continue;
		}
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
	if (isIpInputSelected)
	{
		if (currentIpAddress.empty()) return;

		currentIpAddress.pop_back();
		return;
	}
	
	if (currentPort.empty()) return;

	currentPort.pop_back();
}

void IpAddressInputModal::handleAddText(char charToAdd)
{
	if (isIpInputSelected)
	{
		currentIpAddress.push_back(charToAdd);
		return;
	}
	
	currentPort.push_back(charToAdd);
}
