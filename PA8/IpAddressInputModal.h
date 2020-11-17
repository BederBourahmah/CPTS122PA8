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
	void handleEvents(sf::RenderWindow& window);
private:
	TextComponent* title;
	TextComponent* ipAddressTitle;
	TextComponent* ipAddressInput;

	//Text Input Component
	std::string currentIpAddress;
	void handleTextEnteredEvent(sf::Uint32 enteredChar);
	void handleBackSpace();
	void handleAddText(char charToAdd);
	sf::VideoMode videoMode;
	MoveableRectangle* ipInputBox;
};

#endif // !IP_ADDRESS_INPUT_MODAL_H
