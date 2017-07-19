#include <iostream>

#include "GoGame.h"

int main(int argc, char* argv[]) {
	std::cout << "This program has many features.\n";

	//TODO: Once the game arguments are finalised, pass them in here.
	GoGame* game = new GoGame();

	game->Start();

	delete game;

	return 0;
}