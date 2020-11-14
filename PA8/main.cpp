#include <SFML/Graphics.hpp>
#include <iostream>
#include "VideoHelpers.h"
#include "ScreenManager.h"

using namespace sf;
using namespace std;

int main()
{
    VideoMode fullscreenVideoMode;
    if (!VideoHelpers::getFullscreenVideoMode(fullscreenVideoMode))
    {
        cout << "Failed to get fullscreen video mode." << endl;
        return EXIT_FAILURE;
    }

    RenderWindow window(fullscreenVideoMode, "PA8", Style::Fullscreen);
    ScreenManager screenManager(fullscreenVideoMode);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        screenManager.updateState();
        if (screenManager.shouldExitGame())
        {
            window.close();
            return EXIT_SUCCESS;
        }

        window.clear();
        screenManager.getCurrentScreen()->drawTo(window);
        window.display();
    }

    return EXIT_SUCCESS;
}