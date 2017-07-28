#include "GoGame.h"

#include <iostream>
#include <string>

#include <SFML/OpenGL.hpp>

#include "GameObject.h"

#include "BasicCube.h"
#include "Transform.h"

GoGame::GoGame() {
	//TODO: Arguments eventually.
	sf::VideoMode videoMode;
	videoMode.width = 800;
	videoMode.height = 600;
	systemVars.fullscreen = false;
	window = new sf::Window(videoMode, systemVars.windowTitle, sf::Style::Default);

	// This is to prevent typing style input.
	window->setKeyRepeatEnabled(false);

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

	auto spinningCube = GameObject::Create<BasicCube>();
	spinningCube->SetName("The Cube!");
	auto transform = spinningCube->GetComponent<Transform>();
	transform->Scale() = glm::vec3{0.5f, 0.5f, 0.5f};
	transform->Rotate().z = 0.5f;
	transform->Rotate().x = 0.5f;

	std::cout << "You should see a spinning cube. (it might be straight on)\n";

	// This is a standard while loop described on the documentation page.
	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (!input.HandleInput(event)) {
				if (event.type == sf::Event::Closed) {
					window->close();
				}
			}
		}
		if (input.IsKeyDown(sf::Keyboard::Key::F)) {
			ToggleFullscreen();
		}
		RenderScene();
		window->display();
		input.UpdateState();
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

const Input& GoGame::GetInput() const {
	return input;
}

void GoGame::AddToAwakeQueue(std::shared_ptr<Wakeable> wakeableComponent) {
	awakeQueue.push(std::weak_ptr<Wakeable>(wakeableComponent));
}

void GoGame::RenderScene() {
	//TODO: This is just for demoing. Fix this later on.
	glClearColor(0.1f, 0.1f, 0.7f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-0.1f, 0.1f, -0.1f, 0.1f, 1.0f, 500.0f);

	glDepthMask(true);
	glClearDepth(500.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_LIGHTING);

	glTranslatef(-5.0f, 5.0f, -3.0f);
	glEnable(GL_LIGHT0);

	glTranslatef(5.0f, -5.0f, 3.0f);

	//glTranslatef(0.0f, 0.0f, -3.0f);

	std::shared_ptr<GameObject>(root)->RenderCall();
	
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
}

void GoGame::Awake() {
	while (!awakeQueue.empty()) {
		std::shared_ptr<Wakeable> object = std::shared_ptr<Wakeable>(awakeQueue.front());
		awakeQueue.pop();
		object->Awake();
	}
}

void GoGame::Update() {
	//? Should I be following the tree rather than using my copied list of objects?
	std::vector<std::shared_ptr<GameObject>> copiedObjects;
	for (auto& p : objects) {
		copiedObjects.push_back(p.second);
	}
	for (auto& object : copiedObjects) {
		for (auto& component : object->GetComponents<Updateable>()) {
			if (component->IsActive()) {
				component->Update();
			}
		}
	}
}

void GoGame::LateUpdate() {
	//? Should I be following the tree rather than using my copied list of objects?
	std::vector<std::shared_ptr<GameObject>> copiedObjects;
	for (auto& p : objects) {
		copiedObjects.push_back(p.second);
	}
	for (auto& object : copiedObjects) {
		for (auto& component : object->GetComponents<LateUpdateable>()) {
			if (component->IsActive()) {
				component->LateUpdate();
			}
		}
	}
}
