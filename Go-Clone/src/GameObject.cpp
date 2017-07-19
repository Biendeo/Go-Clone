#include "GameObject.h"

#include "GoGame.h"

GoGame* GameObject::engine = nullptr;
uint32_t GameObject::nextID = 1;

GameObject* GameObject::CreateRootObject(GoGame* engine) {
	GameObject::engine = engine;
	GameObject::nextID = 1;
	GameObject* root = new GameObject();
	root->SetName("ROOT");
	return root;
}

GameObject::GameObject() {
	this->parent = engine->GetRootObject();
	SetID(nextID++);
	engine->RegisterObject(std::shared_ptr<GameObject>(this));
}

GameObject::GameObject(std::shared_ptr<GameObject> parent) : GameObject() {
	this->parent = parent;
}


GameObject::~GameObject() {
	// Huh?
	if (true) {
		int x = 0;
	}
}

void GameObject::Destroy(std::shared_ptr<GameObject> object) {
	//TODO: Once children are set up, destroy all the children, and clean up variables.
	engine->UnregisterObject(object);
}

uint32_t GameObject::GetID() const {
	return ID;
}

uint32_t GameObject::SetID(uint32_t newID) {
	this->ID = newID;
	return newID;
}

std::string GameObject::GetName() const {
	return name;
}

void GameObject::SetName(const std::string& newName) {
	this->name = newName;
}