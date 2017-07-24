#pragma once

#include <SFML/Window.hpp>

//! This may not be enough for all purposes (eg. typing, or precise mouse movement).
/// <summary>
/// Handles per-frame inputs and states. SFML events should be passed in, and the state is managed internally.
/// </summary>
class Input {
	public:
	/// <summary>
	/// Sets up the internal structures for handling input.
	/// </summary>
	Input();
	~Input();

	/// <summary>
	/// Marks the current state as finished and creates a new one.
	/// This should be called at the end of a frame draw so that new events are counted under
	/// a new frame.
	/// </summary>
	void UpdateState();

	/// <summary>
	/// Handles an SFML event for the current state.
	/// </summary>
	/// <param name="event">The SFML event to be handled.</param>
	/// <returns>True if the event was of an input change. If false, the engine should handle this.</returns>
	bool HandleInput(sf::Event event);

	/// <summary>
	/// Gets whether the given key was pressed down in the last update.
	/// </summary>
	/// <param name="key">The key that was pressed.</param>
	/// <returns>Whether it was pressed down in the last update.</returns>
	bool GetKeyDown(sf::Keyboard::Key key) const;

	/// <summary>
	/// Gets whether the given key was released in the last update.
	/// </summary>
	/// <param name="key">The key that was released.</param>
	/// <returns>Whether it was released in the last update.</returns>
	bool GetKeyUp(sf::Keyboard::Key key) const;

	/// <summary>
	/// Gets whether the given key is current down as of the last update.
	/// </summary>
	/// <param name="key">The key that is down.</param>
	/// <returns>Whether it is currently down in the last update.</returns>
	bool GetKey(sf::Keyboard::Key key) const;

	private:
	/// <summary>
	/// The previous input state. Used internally to see what input has changed.
	/// </summary>
	struct InputState* previousState;
	/// <summary>
	/// The current input state. Used internally to see what the current input is.
	/// </summary>
	struct InputState* currentState;
	/// <summary>
	/// The next input state. Used internally to plan for what the next state will have.
	/// </summary>
	struct InputState* nextState;
};