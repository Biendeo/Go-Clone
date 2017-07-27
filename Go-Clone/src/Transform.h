#pragma once

#include <glm/vec3.hpp>

#include "Component.h"

class Transform : public Component {
	public:
	Transform(GameObject* gameObject);
	~Transform();

	glm::vec3& Translate();
	glm::vec3& Rotate();
	glm::vec3& Scale();

	protected:
	//TODO: I realised this doesn't work, redo this system.
	static const bool unique = true;

	private:
	glm::vec3 translate;
	glm::vec3 rotate;
	glm::vec3 scale;
};

