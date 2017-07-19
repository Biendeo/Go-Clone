#include "GoGame.h"

#include <iostream>
#include <string>

#include <SFML/OpenGL.hpp>


GoGame::GoGame() {
	//TODO: Arguments eventually.
	sf::VideoMode videoMode;
	videoMode.width = 800;
	videoMode.height = 600;
	systemVars.fullscreen = false;
	window = new sf::Window(videoMode, systemVars.windowTitle, sf::Style::Default);

	root = std::shared_ptr<GameObject>(nullptr);
	// Since root is nullptr right now, then the construction of the root object should correctly have a nullptr parent.
	GameObject::CreateRootObject(this);
	root = objects.at(1);
}


GoGame::~GoGame() {
	std::shared_ptr<GameObject>(root)->Destroy();
	delete window;
}

void GoGame::Start() {
	std::cout << "We're in the start function!\n";

	//! Remove this in production.
	std::cout << "Putting in a couple of dummy objects and deleting them quickly.\n";
	std::cout << "If the memory goes up, then there's a leak somewhere.\n";

	for (int i = 0; i < 10000; ++i) {
		auto dummyOne = GameObject::Create<GameObject>();
		dummyOne->SetName("Item 1");
		auto dummyTwo = GameObject::Create<GameObject>(dummyOne);
		dummyTwo->SetName("Item 2");

		dummyOne->Destroy();
	}

	std::cout << "Seems okay.\n";

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

	std::cout << "The program is now exiting!\n";
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
	if (!systemVars.fullscreen) {
		window = new sf::Window(sf::VideoMode(systemVars.screenWidth, systemVars.screenHeight), systemVars.windowTitle, sf::Style::Fullscreen);
		systemVars.fullscreen = true;
	} else {
		window = new sf::Window(sf::VideoMode(systemVars.windowWidth, systemVars.windowHeight), systemVars.windowTitle, sf::Style::Default);
		systemVars.fullscreen = false;
	}
	return systemVars.fullscreen;
}

std::shared_ptr<GameObject> GoGame::GetRootObject() {
	// Weak pointers can't be promoted to shared pointers if they're null.
	// This check should get this to work properly.
	if (root.expired()) {
		return std::shared_ptr<GameObject>(nullptr);
	} else {
		return std::shared_ptr<GameObject>(root);
	}
}

void GoGame::RegisterObject(std::shared_ptr<GameObject> object) {
	objects.insert(std::make_pair(object->GetID(), object));
}

void GoGame::UnregisterObject(std::shared_ptr<GameObject> object) {
	objects.erase(object->GetID());
}

std::shared_ptr<GameObject> GoGame::GetSharedPointer(uint32_t ID) {
	return std::shared_ptr<GameObject>(objects.at(ID));
}

void GoGame::RenderScene() {
	//TODO: This is just for demoing. Fix this later on.
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