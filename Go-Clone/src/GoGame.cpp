#include "GoGame.h"

#include <iostream>
#include <string>

#include <SFML/OpenGL.hpp>


GoGame::GoGame() {
	//TODO: Arguments eventually.
	std::string windowTitle = "Go Game";
	sf::VideoMode videoMode;
	videoMode.width = 800;
	videoMode.height = 600;
	sf::Uint32 style = sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close;
	window = new sf::Window(videoMode, windowTitle, style);
}


GoGame::~GoGame() {
	delete window;
}

void GoGame::Start() {
	//TODO: Create a game loop.
	std::cout << "We're in the start function!\n";
	std::cout << "If you see a rainbow traingle in the top-right corner, you're good!\n";

	// This is a standard while loop described on the documentation page.
	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			} else {
				RenderScene();
				window->display();
			}
		}
	}
}

const GameState& GoGame::GetGameState() const {
	return gameState;
}

void GoGame::RenderScene() {
	glClearColor(0.1f, 0.1f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, window->getSize().x, window->getSize().y);
	glBegin(GL_TRIANGLES);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.2, 0.2);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.8, 0.2);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0.5, 0.8);

	glEnd();
}