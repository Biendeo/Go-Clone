#include "Transform.h"



Transform::Transform(GameObject* gameObject) : Component(gameObject) {
	translate = glm::vec3(0.0f, 0.0f, 0.0f);
	rotate = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(0.0f, 0.0f, 0.0f);
}


Transform::~Transform() {

}

glm::vec3& Transform::Translate() {
	return translate;
}

glm::vec3& Transform::Rotate() {
	return rotate;
}

glm::vec3& Transform::Scale() {
	return scale;
}
