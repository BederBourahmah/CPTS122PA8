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
        screenManager.updateState();
        if (screenManager.shouldExitGame())
        {
            window.close();
            return EXIT_SUCCESS;
        }

        screenManager.getCurrentScreen()->handleEvents(window);
        window.clear();
        screenManager.getCurrentScreen()->drawTo(window);
        window.display();
    }

    return EXIT_SUCCESS;
}