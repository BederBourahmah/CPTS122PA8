#ifndef LOADING_MODAL_H
#define LOADING_MODAL_H

#include "Modal.h"

class LoadingModal : public Modal
{
public:
	LoadingModal(sf::VideoMode vm);
	~LoadingModal();

	void drawTo(sf::RenderWindow& window);
	void updateState();

private:
	sf::VideoMode videoMode;
	sf::Texture iconTexture;
	sf::RectangleShape gearIcon;
	sf::Clock rotationClock;
	const float degreesPerMillisecond = 180.0f / 1000.0f;
};

#endif // !LOADING_MODAL_H
