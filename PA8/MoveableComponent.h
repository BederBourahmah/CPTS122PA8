#ifndef MOVEABLE_COMPONENT_H
#define MOVEABLE_COMPONENT_H

#include <SFML/Graphics.hpp>

class MoveableComponent
{
public:
	virtual void centerHorizontal(sf::VideoMode const videoMode)=0;
	virtual void snapToVertical(sf::VideoMode const videoMode, int sections, int sectionToSnapTo)=0;
private:

};

#endif // !MOVEABLE_COMPONENT_H
