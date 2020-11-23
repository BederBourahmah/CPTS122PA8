#ifndef SINGLE_OR_MULTIPLAYER_MODAL_H
#define SINGLE_OR_MULTIPLAYER_MODAL_H

#include "Modal.h"
#include "TextComponent.h"

class SingleOrMultiplayerModal : public Modal
{
public:
	SingleOrMultiplayerModal(sf::VideoMode vm);
	~SingleOrMultiplayerModal();

	void drawTo(sf::RenderWindow& window);
	void handleEvents(sf::RenderWindow& window);
	bool getIsSinglePlayer();
	bool getIsReady();
	bool getIsCancelling();

private:
	TextComponent* singlePlayerButton;
	TextComponent* multiPlayerButton;
	TextComponent* cancelButton;

	void processMouseClick(sf::Vector2i mousePosition);
	bool isSinglePlayerSelected;
	bool isReady;
	bool isCancelling;
};

#endif // !SINGLE_OR_MULTIPLAYER_MODAL_H
