#include "GoGame.h"

#include <iostream>


GoGame::GoGame() {
	//TODO: Arguments eventually.
	//TODO: Maybe split up the video mode to see what you can put in it.
	window = new sf::Window(sf::VideoMode(800, 600), "Go Game");
}


GoGame::~GoGame() {
	delete window;
}

void GoGame::Start() {
	//TODO: Create a game loop.
	std::cout << "We're in the start function!\n";
}

const GameState& GoGame::GetGameState() const {
	return gameState;
}
