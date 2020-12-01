#include "IpAddressInputModal.h"

IpAddressInputModal::IpAddressInputModal(sf::VideoMode vm) : Modal(ModalSize::Medium, vm)
{
	videoMode = vm;
	title = new TextComponent("Leander.ttf", "Input IP Address and Port", 20);
	title->centerHorizontal(videoMode);
	title->snapToVertical(videoMode, 16, 4);

	ipAddressTitle = new TextComponent("Leander.ttf", "IP Address", 18);
	ipAddressTitle->centerHorizontal(videoMode);
	ipAddressTitle->snapToVertical(videoMode, 16, 6);

	ipAddressInput = new TextComponent("Leander.ttf", "", 18, sf::Color::Green);
	ipAddressInput->centerHorizontal(videoMode);
	ipAddressInput->snapToVertical(videoMode, 16, 8);

	float boxHeight = (50.0f / 1080.0f)*videoMode.height;
	ipInputBox = new MoveableRectangle(sf::Vector2f(0.2f * videoMode.width, boxHeight), sf::Color::Black);
	ipInputBox->centerHorizontal(videoMode);
	ipInputBox->snapToVertical(videoMode, 16, 8);

	portTitle = new TextComponent("Leander.ttf", "Port", 18);
	portTitle->centerHorizontal(videoMode);
	portTitle->snapToVertical(videoMode, 16, 10);

	portInput = new TextComponent("Leander.ttf", "", 18, sf::Color::Green);
	portInput->centerHorizontal(videoMode);
	portInput->snapToVertical(videoMode, 16, 12);

	portInputBox = new MoveableRectangle(sf::Vector2f(0.2f * videoMode.width, boxHeight), sf::Color::Black);
	portInputBox->centerHorizontal(videoMode);
	portInputBox->snapToVertical(videoMode, 16, 12);

	boxHighlighter = new MoveableRectangle(sf::Vector2f(0.2f * videoMode.width + 5, boxHeight+5), sf::Color::Red);
	boxHighlighter->centerHorizontal(videoMode);
	boxHighlighter->snapToVertical(videoMode, 16, 8);

	okButton = new TextComponent("Leander.ttf", "OK", 25);
	okButton->snapToHorizontal(videoMode, 8, 4);
	okButton->snapToVertical(videoMode, 16, 13);

	cancelButton = new TextComponent("Leander.ttf", "Cancel", 25);
	cancelButton->snapToHorizontal(videoMode, 8, 5);
	cancelButton->snapToVertical(videoMode, 16, 13);

	serverButton = new TextComponent("Leander.ttf", "Server", 18);
	serverButton->snapToHorizontal(videoMode, 8, 4);
	serverButton->snapToVertical(videoMode, 16, 5);

	clientButton = new TextComponent("Leander.ttf", "Client", 18);
	clientButton->snapToHorizontal(videoMode, 8, 5);
	clientButton->snapToVertical(videoMode, 16, 5);

	isIpInputSelected = true;
	isReady = false;
	isServer = false;
	isCancelling = false;
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
	delete serverButton;
	serverButton = nullptr;
	delete clientButton;
	clientButton = nullptr;
	delete cancelButton;
	cancelButton = nullptr;
}

void IpAddressInputModal::drawTo(sf::RenderWindow& window)
{
	Modal::drawTo(window);
	title->drawTo(window);
	ipAddressInput->centerHorizontal(videoMode);
	boxHighlighter->drawTo(window);
	if (!isServer)
	{
		ipAddressTitle->drawTo(window);
		ipInputBox->drawTo(window);
		ipAddressInput->drawTo(window);
	}
	
	portTitle->drawTo(window);
	portInputBox->drawTo(window);
	portInput->drawTo(window);
	okButton->drawTo(window);
	serverButton->drawTo(window);
	clientButton->drawTo(window);
	cancelButton->drawTo(window);
}

void IpAddressInputModal::updateState()
{
	ipAddressInput->setText(currentIpAddress);
	portInput->setText(currentPort);
}

void IpAddressInputModal::processMouseClick(sf::Vector2i mousePosition)
{
	if (portInputBox->isPositionInMyArea(mousePosition))
	{
		boxHighlighter->snapToVertical(videoMode, 16, 12);
		isIpInputSelected = false;
		return;
	}

	if (ipInputBox->isPositionInMyArea(mousePosition))
	{
		boxHighlighter->snapToVertical(videoMode, 16, 8);
		isIpInputSelected = true;
		return;
	}

	if (okButton->isPositionInMyArea(mousePosition))
	{
		if (currentPort.empty()) return;
		if (!isServer && currentIpAddress.empty()) return;

		isReady = true;
		return;
	}

	if (serverButton->isPositionInMyArea(mousePosition))
	{
		isServer = true;
		boxHighlighter->snapToVertical(videoMode, 16, 12);
		isIpInputSelected = false;
		currentIpAddress.clear();
		return;
	}

	if (clientButton->isPositionInMyArea(mousePosition))
	{
		isServer = false;
		return;
	}

	if (cancelButton->isPositionInMyArea(mousePosition))
	{
		isCancelling = true;
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

		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				processMouseClick(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			}
			continue;
		}
	}
}

bool IpAddressInputModal::getIsReady()
{
	return isReady;
}

std::string IpAddressInputModal::getAddress()
{
	return currentIpAddress;
}

unsigned short IpAddressInputModal::getPort()
{
	int intValue = 0;
	try
	{
		intValue = std::stoi(currentPort, nullptr, 10);
	}
	catch (const std::exception&)
	{
		return 0;
	}

	if (intValue > USHRT_MAX || intValue < 0)
	{
		return 0;
	}

	return (unsigned short)intValue;
}

bool IpAddressInputModal::getIsServer()
{
	return isServer;
}

bool IpAddressInputModal::getIsCancelling()
{
	return isCancelling;
}

void IpAddressInputModal::resetState()
{
	isIpInputSelected = true;
	isReady = false;
	isServer = false;
	isCancelling = false;
	portInput->setText("");
	ipAddressInput->setText("");
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
