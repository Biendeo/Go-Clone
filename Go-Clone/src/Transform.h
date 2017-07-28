#pragma once

#include <glm/vec3.hpp>

#include "Component.h"

/// <summary>
/// A basic structure that can define the position of an object in the world.
/// The values of this is relative to the parent object.
/// </summary>
class Transform : public Component {
	public:
	Transform(GameObject* gameObject);
	~Transform();

	/// <summary>
	/// Returns the translation (position) of the object.
	/// </summary>
	/// <returns>The translation (position) of the object.</returns>
	glm::vec3& Translate();

	/// <summary>
	/// Returns the rotation of the object (in Euler angles (radiens)).
	/// </summary>
	/// <returns>The rotation of the object (in Euler angles (radiens)).</returns>
	glm::vec3& Rotate();

	/// <summary>
	/// Returns the scale of the object.
	/// </summary>
	/// <returns>The scale of the object.</returns>
	glm::vec3& Scale();

	//TODO: Add support for getting global positions.

	static const bool unique = true;

	protected:

	private:
	glm::vec3 translate;
	glm::vec3 rotate;
	glm::vec3 scale;
};

