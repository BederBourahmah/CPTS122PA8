#ifndef MODAL_H
#define MODAL_H

#include "ModalSize.h"
#include <SFML/Graphics.hpp>
#include "ModalBorder.h"
#include "MoveableComponent.h"

class Modal : public MoveableComponent
{
public:
	Modal(ModalSize s, sf::VideoMode vm);
	~Modal();

	void drawTo(sf::RenderWindow& window);

private:
	void updatePosition();
	bool loadModalBackgroundTexture();
	bool loadModalBackground();
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::VideoMode videoMode;
	float getWidthByModalSize();
	float getInnerLeftFromCenter();
	float getInnerTopFromCenter();
	ModalSize size;
	ModalBorder* border;
};

#endif // !MODAL_H
