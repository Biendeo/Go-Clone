#include "GameObject.h"

#include "GoGame.h"

GoGame* GameObject::engine = nullptr;
uint32_t GameObject::nextID = 1;

std::shared_ptr<GameObject> GameObject::CreateRootObject(GoGame* engine) {
	GameObject::engine = engine;
	GameObject::nextID = 1;
	GameObject* root = new GameObject();
	root->SetName("ROOT");
	return root->GetSharedPointer();
}

void GameObject::RemoveComponent(Component* component) {
	for (size_t i = 0; i < components.size(); ++i) {
		if (components[i].get() == component) {
			components.erase(components.begin() + i);
			break;
		}
	}
}

GoGame* GameObject::GetEngine() {
	return engine;
}

void GameObject::RenderCall() {
	//TODO: Add a is enabled call.
	std::vector<std::shared_ptr<Renderable>> renderComponents = GetComponents<Renderable>();

	// Your render components should modify anything, so this should be fine.
	for (auto& renderComponent : renderComponents) {
		if (renderComponent->IsActive()) {
			renderComponent->Render();
		}
	}

	for (auto& childPair : children) {
		std::shared_ptr<GameObject> child = std::shared_ptr<GameObject>(childPair.second);
		child->RenderCall();
	}
}

GameObject::GameObject() {
	SetID(nextID++);
	engine->RegisterObject(std::shared_ptr<GameObject>(this));
	SetParent(engine->GetRootObject());
}

GameObject::GameObject(std::shared_ptr<GameObject> parent) : GameObject() {
	SetParent(parent);
}


GameObject::~GameObject() {

}

void GameObject::Destroy() {
	for (auto child : GetChildren()) {
		std::shared_ptr<GameObject>(child)->Destroy();
	}

	if (ID != 1) {
		std::shared_ptr<GameObject> parent = std::shared_ptr<GameObject>(this->parent);
		parent->children.erase(ID);
	}

	engine->UnregisterObject(GetSharedPointer());
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

std::shared_ptr<GameObject> GameObject::GetParent() const {
	return std::shared_ptr<GameObject>(parent);
}

void GameObject::SetParent(std::shared_ptr<GameObject> newParent) {
	// Here is an added check if the object is the root object.
	if (newParent == nullptr && ID == 1) {
		this->parent = newParent;
	} else {
		// If a parent exists yet, then it needs to be removed.
		if (!parent.expired()) {
			std::shared_ptr<GameObject> oldParent = std::shared_ptr<GameObject>(parent);
			oldParent->children.erase(ID);
		}
		//TODO: Move the object so that it remains in the same location globally.
		this->parent = newParent;
		newParent->children.insert(std::make_pair(ID, GetSharedPointer()));
	}
}

std::shared_ptr<GameObject> GameObject::GetSharedPointer() {
	return engine->GetSharedPointer(ID);
}

std::vector<std::shared_ptr<GameObject>> GameObject::GetChildren() {
	std::vector<std::shared_ptr<GameObject>> v;
	for (auto child : children) {
		v.push_back(std::shared_ptr<GameObject>(child.second));
	}

	return v;
}
