#include "Component.h"

#include "GameObject.h"
#include "GoGame.h"

Component::Component(GameObject* gameObject) {
	this->gameObject = gameObject;
}


Component::~Component() {
}

void Component::Destroy() {

}

std::shared_ptr<GameObject> Component::GetGameObject() {
	return gameObject->GetEngine()->GetSharedPointer(gameObject->GetID());
}
