#include "ComponentTypes.h"

#include "GameObject.h"
#include "GoGame.h"

ComponentType::ComponentType(GameObject* gameObject) : Component(gameObject) {}

bool ComponentType::IsActive() const {
	return active;
}

void ComponentType::SetActive(bool active) {
	this->active = active;
}

Wakeable::Wakeable(GameObject* gameObject) : ComponentType(gameObject) {
	//? I dunno if this will work 100% of the time, double check this.
	gameObject->GetEngine()->AddToAwakeQueue(std::shared_ptr<Wakeable>(this));
}

Updateable::Updateable(GameObject* gameObject) : ComponentType(gameObject) {}

LateUpdateable::LateUpdateable(GameObject* gameObject) : ComponentType(gameObject) {}

Renderable::Renderable(GameObject* gameObject) : ComponentType(gameObject) {}