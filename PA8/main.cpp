#include <SFML/Graphics.hpp>
#include <iostream>
#include "VideoHelpers.h"
#include "MenuSelector.h"
#include "TextComponent.h"
#include "MainMenu.h"
#include "Screens.h"

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
    MainMenu* mainMenu = new MainMenu(fullscreenVideoMode);

    CurrentScreen currentScreen = CurrentScreen::MainMenu;

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

        if (currentScreen == CurrentScreen::MainMenu && mainMenu != nullptr)
        {
            mainMenu->processKeyboardInput();
            mainMenu->processMousePosition(Mouse::getPosition());
            mainMenu->processMouseClick();
            if (mainMenu->shouldExitGame())
            {
                window.close();
            }
        }

        window.clear();

        if (currentScreen == CurrentScreen::MainMenu && mainMenu != nullptr)
        {
            mainMenu->drawTo(window);
        }

        window.display();
        if (currentScreen == CurrentScreen::MainMenu)
        {
            cout << "Main Menu" << endl;
        }
    }

    return EXIT_SUCCESS;
}