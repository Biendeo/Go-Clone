#include "Input.h"

#include <array>

/// <summary>
/// An instant of all the current input. Everything should exist within this.
/// </summary>
struct InputState {
	static const uint8_t totalKeys = sf::Keyboard::Key::KeyCount;
	std::array<bool, totalKeys> keyboardState;
	//TODO: Add more stuff here for more inputs.
};

Input::Input() {
	// This assumes that they will initialise completely as false.
	previousState = new InputState;
	currentState = new InputState;
	nextState = new InputState;
}

Input::~Input() {
	//HACK: This extra check can probably be removed; an older style of using the states needed this.
	if (currentState != nextState) {
		delete nextState;
	}
	if (previousState != currentState) {
		delete currentState;
	}
	delete previousState;
}

void Input::UpdateState() {
	// All the pointers swap. This should allow the data to be quickly transferred.
	delete previousState;
	previousState = currentState;
	currentState = nextState;
	nextState = new InputState;
	// Copy all the info from the current state into the next state so it can be modified independently.
	*nextState = *currentState;
}

bool Input::HandleInput(sf::Event event) {
	switch (event.type) {
		case sf::Event::EventType::KeyPressed:
			nextState->keyboardState[event.key.code] = true;
			break;
		case sf::Event::EventType::KeyReleased:
			nextState->keyboardState[event.key.code] = false;
			break;
		case sf::Event::EventType::JoystickButtonPressed:
		case sf::Event::EventType::JoystickButtonReleased:
		case sf::Event::EventType::MouseButtonPressed:
		case sf::Event::EventType::MouseButtonReleased:
		case sf::Event::EventType::MouseMoved:
			//TODO: Handle everything else at some point.
			break;
		// If the input is none of these, then don't act on it, and return false.
		// The engine should pick up on this and then act on it.
		default:
			return false;
	}
	return true;
}

bool Input::GetKeyDown(sf::Keyboard::Key key) const {
	return currentState->keyboardState[key] && !previousState->keyboardState[key];
}

bool Input::GetKeyUp(sf::Keyboard::Key key) const {
	return !currentState->keyboardState[key] && previousState->keyboardState[key];
}

bool Input::GetKey(sf::Keyboard::Key key) const {
	return currentState->keyboardState[key];
}