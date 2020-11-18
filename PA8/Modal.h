#ifndef MODAL_H
#define MODAL_H

#include "ModalSize.h"
#include <SFML/Graphics.hpp>
#include "ModalBorder.h"
#include "GUIComponent.h"

class Modal : public GUIComponent
{
public:
	Modal(ModalSize s, sf::VideoMode vm);
	~Modal();

	void drawTo(sf::RenderWindow& window);

private:
	void updatePosition();
	bool loadModalBackground();
	sf::RectangleShape background;
	sf::VideoMode videoMode;
	float getWidthByModalSize();
	float getHeightByModalSize();
	float getInnerLeftFromCenter();
	float getInnerTopFromCenter();

	ModalSize size;
	ModalBorder* border;
};

#endif // !MODAL_H
