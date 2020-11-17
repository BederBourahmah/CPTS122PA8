#ifndef IP_ADDRESS_INPUT_MODAL_H
#define IP_ADDRESS_INPUT_MODAL_H

#include "Modal.h"
#include "TextComponent.h"
#include "MoveableRectangle.h"

class IpAddressInputModal : public Modal
{
public:
	IpAddressInputModal(sf::VideoMode vm);
	~IpAddressInputModal();
	
	void drawTo(sf::RenderWindow& window);
	void updateState();
	void processMouseClick(sf::Vector2i mousePosition);
	void handleEvents(sf::RenderWindow& window);
private:
	TextComponent* title;
	TextComponent* ipAddressTitle;
	TextComponent* ipAddressInput;
	TextComponent* portTitle;
	TextComponent* portInput;

	//Text Input Component
	std::string currentIpAddress;
	std::string currentPort;
	void handleTextEnteredEvent(sf::Uint32 enteredChar);
	void handleBackSpace();
	void handleAddText(char charToAdd);
	sf::VideoMode videoMode;
	MoveableRectangle* ipInputBox;
	MoveableRectangle* portInputBox;
	MoveableRectangle* boxHighlighter;
	bool isIpInputSelected;
};

#endif // !IP_ADDRESS_INPUT_MODAL_H
