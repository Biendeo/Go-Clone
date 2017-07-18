#pragma once

#include <SFML/Window.hpp>

#include "GameState.h"

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

	private:
	GameState gameState;

	//? Should I be using a smart pointer here?
	sf::Window* window;
};

