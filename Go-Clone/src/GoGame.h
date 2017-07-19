#pragma once

#include <SFML/Window.hpp>

#include "GameState.h"

/// <summary>
/// Stores information about the current system, this is mostly used for window management and hardware polling.
/// </summary>
struct SystemVariables {
	bool fullscreen;
	sf::Uint32 windowWidth;
	sf::Uint32 windowHeight;
	sf::Uint32 screenWidth;
	sf::Uint32 screenHeight;
	const std::string windowTitle = "Go Game";
};

/// <summary>
/// The main class of the game. This should be made immediately in main, and arguments should be passed to it.
/// </summary>
class GoGame {
	public:
	GoGame();
	~GoGame();

	/// <summary>
	/// Starts the game. This should be called immediately after construction.
	/// </summary>
	void Start();

	/// <summary>
	/// Returns the game state object for classes to refer to.
	/// </summary>
	const GameState& GetGameState() const;

	/// <summary>
	/// Switches the program to and from fullscreen.
	/// </summary>
	/// <returns>Whether the program is now fullscreen or not.</returns>
	bool ToggleFullscreen();

	private:
	/// <summary>
	/// Renders the current game scene. This should only be called in the game loop.
	/// </summary>
	void RenderScene();

	GameState gameState;

	//? Should I be using a smart pointer here?
	sf::Window* window;
	SystemVariables systemVars;
};