#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "TextComponent.h"
#include "MenuSelector.h"
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "Screens.h"
#include "MainMenuSelection.h"
#include "IpAddressInputModal.h"
#include "TcpServer.h"
#include "TcpClient.h"
#include "LoadingModal.h"
#include "SingleOrMultiplayerModal.h"

class ScreenManager;

class MainMenu : public Screen
{
public:
	/// <summary>
	/// Initializes the internal copy of the video mode, a pointer to the parent screen manager, and a callback function for
	/// connecting to the network.
	/// </summary>
	/// <param name="vm">The video mode that will render this screen.</param>
	/// <param name="manager">A pointer to the parent manager.</param>
	/// <param name="connectToNetworkCallback">A callback function for connecting to the network.</param>
	MainMenu(sf::VideoMode const vm, ScreenManager *manager, void(ScreenManager::* connectToNetworkCallback)(std::string addr, unsigned int port, bool isServer));

	~MainMenu();

	/// <summary>
	/// This function draws all sprites rendered by this screen to the window.
	/// </summary>
	/// <param name="window">The window that will render the contents of this screen.</param>
	void drawTo(sf::RenderWindow &window);

	/// <summary>
	/// Moves the menu selector down one option, unless it is already at the bottom of the available options.
	/// </summary>
	void moveSelectorDown();

	/// <summary>
	/// Moves the menu selector up one option, unless it is already at the top of the available options.
	/// </summary>
	void moveSelectorUp();

	/// <summary>
	/// Processes the user's keyboard input.
	/// </summary>
	void processKeyboardInput();

	/// <summary>
	/// Processes the position of the user's mouse. Used to changing the position of the menu selector when the mouse hovers over different buttons.
	/// </summary>
	/// <param name="mouseWindowPosition">The current mouse position.</param>
	void processMousePosition(sf::Vector2i mouseWindowPosition);

	/// <summary>
	/// Gets the value of the private variable that is set to true when the user selects an option to leave the game.
	/// </summary>
	/// <returns>True if the user has selected to exit the game.</returns>
	bool shouldExitGame();

	/// <summary>
	/// Gets the value of the private enum used to track the selected screen.
	/// </summary>
	/// <returns>The enum value of the screen selected by the user.</returns>
	Screens getSelectedScreen();

	/// <summary>
	/// Handles the events that have been generated for the window.
	/// </summary>
	/// <param name="window">The window that is generating the events.</param>
	void handleEvents(sf::RenderWindow& window);

	/// <summary>
	/// Updates the internal state of this screen.
	/// </summary>
	void updateState();

private:
	TextComponent* howToPlayText;

	/// <summary>
	/// A pointer to the text component representing the button for selecting the swarm defender game.
	/// </summary>
	TextComponent* swarmDefenderText;

	/// <summary>
	/// A pointer to the text component representing the button for exiting the game.
	/// </summary>
	TextComponent* exitText;

	/// <summary>
	/// A pointer to the menu selector.
	/// </summary>
	MenuSelector* selector;

	/// <summary>
	/// The user's menu selection.
	/// </summary>
	MainMenuSelection currentSelection;

	/// <summary>
	/// The screen selected by the user.
	/// </summary>
	Screens selectedScreen;

	/// <summary>
	/// Updates the position of the menu selector to match the current user selection.
	/// </summary>
	void updateSelectorPosition();

	/// <summary>
	/// The sprite containing the background texture.
	/// </summary>
	sf::Sprite backgroundSprite;

	/// <summary>
	/// The texture containing the background image.
	/// </summary>
	sf::Texture backgroundTexture;

	/// <summary>
	/// Loads the background texture for this screen.
	/// </summary>
	/// <returns>True if the background loaded successfully.</returns>
	bool loadMainMenuBackgroundTexture();

	/// <summary>
	/// Loads the background sprite for this screen.
	/// </summary>
	/// <param name="videoMode">The video mode that will render the background.</param>
	/// <returns>True if the background loaded successfully.</returns>
	bool loadMainMenuBackgroundSprite(sf::VideoMode const videoMode);

	/// <summary>
	/// Handles a key press event.
	/// </summary>
	/// <param name="event">The key press event.</param>
	void handleKeyPressEvent(sf::Event event);

	/// <summary>
	/// A pointer to the network connection modal.
	/// </summary>
	IpAddressInputModal* networkConnectionModal;

	/// <summary>
	/// Handles the user's request to connect to the network, calling the callback function passed in to the constructor.
	/// </summary>
	void handleConnectToNetwork();

	/// <summary>
	/// The video mode that will render this screen.
	/// </summary>
	sf::VideoMode videoMode;

	/// <summary>
	/// Is set to true when the options in the menu are disabled, such as when a modal appears.
	/// </summary>
	/// <returns>True when all main menu options are disabled.</returns>
	bool isMenuDisabled();

	/// <summary>
	/// A pointer to the single or multiplayer selection modal.
	/// </summary>
	SingleOrMultiplayerModal* singVsMultiModal;

	/// <summary>
	/// Is set to true when the singVsMultiModal is displayed.
	/// </summary>
	bool isSingleVsMultiplayerModalDisplayed;

	/// <summary>
	/// Is set to true when the networkConnectionModal is displayed.
	/// </summary>
	bool isNetworkConnectionModalDisplayed;

	/// <summary>
	/// Closes the SingleOrMultiplayerModal.
	/// </summary>
	void closeSingleVsMultiplayerModal();

	/// <summary>
	/// Closes the network connection modal and resets its state.
	/// </summary>
	void closeNetworkConnectionModal();

	/// <summary>
	/// The callback function for connecting to the network.
	/// </summary>
	void(ScreenManager::* onConnectToNetwork)(std::string addr, unsigned int port, bool isServer);

	/// <summary>
	/// The parent ScreenManager that has this screen as one of its members as well as the callback functions.
	/// </summary>
	ScreenManager* parentManager;

	/// <summary>
	/// Handles a click event.
	/// </summary>
	/// <param name="event">A click event.</param>
	void handleClickEvent(sf::Event event);
};

#endif // !MAIN_MENU_H