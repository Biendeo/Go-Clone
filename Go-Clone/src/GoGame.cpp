#include "GoGame.h"

#include <iostream>
#include <string>

#include <SFML/OpenGL.hpp>


GoGame::GoGame() {
	//TODO: Arguments eventually.
	sf::VideoMode videoMode;
	videoMode.width = 800;
	videoMode.height = 600;
	window = new sf::Window(videoMode, systemVars.windowTitle, sf::Style::Default);
}


GoGame::~GoGame() {
	delete window;
}

void GoGame::Start() {
	std::cout << "We're in the start function!\n";
	std::cout << "If you see a rainbow traingle in the top-right corner, you're good!\n";

	// This is a standard while loop described on the documentation page.
	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			} else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F) {
				ToggleFullscreen();
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

bool GoGame::ToggleFullscreen() {
	delete window;
	systemVars.windowWidth = 800;
	systemVars.windowHeight = 600;
	systemVars.screenWidth = sf::VideoMode::getDesktopMode().width;
	systemVars.screenHeight = sf::VideoMode::getDesktopMode().height;
	if (systemVars.fullscreen) {
		window = new sf::Window(sf::VideoMode(systemVars.screenWidth, systemVars.screenHeight), systemVars.windowTitle, sf::Style::Fullscreen);
		systemVars.fullscreen = false;
	} else {
		window = new sf::Window(sf::VideoMode(systemVars.windowWidth, systemVars.windowHeight), systemVars.windowTitle, sf::Style::Default);
		systemVars.fullscreen = true;
	}
	return systemVars.fullscreen;
}

void GoGame::RenderScene() {
	glClearColor(0.1f, 0.1f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, window->getSize().x, window->getSize().y);
	glBegin(GL_TRIANGLES);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.2f, 0.2f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.8f, 0.2f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0.5f, 0.8f);

	glEnd();
}