#include "BasicCube.h"

#include <SFML/OpenGL.hpp>

#include "ComponentTypes.h"
#include "Transform.h"

/// <summary>
/// Just a basic class for rotating the cube.
/// </summary>
class AutoRotate : public Updateable {
	public:
	AutoRotate(GameObject* object) : Updateable(object) {}

	void Update() override {
		auto transform = GetGameObject()->GetComponent<Transform>();
		transform->Rotate().y += 0.0001f;
		transform->Rotate().x += 0.00001f;
	}
};

class CubeRenderer : public Renderable {
	public:
	CubeRenderer(GameObject* gameObject) : Renderable(gameObject) {
		color = glm::vec3(0.5f, 0.5f, 0.5f);
	}

	void Render() override {
		glColor3f(color.r, color.g, color.b);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		//TODO: Change this to pre-buffered objects.
		glPolygonMode(GL_FRONT, GL_FILL);
		//glPolygonMode(GL_BACK, GL_NEVER);
		glBegin(GL_TRIANGLES);

		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);

		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);

		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);

		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		glEnd();
	}

	glm::vec3 GetColor() {
		return color;
	}

	private:
	glm::vec3 color;
};


BasicCube::BasicCube() : GameObject() {
	AddComponent<Transform>();
	AddComponent<CubeRenderer>();
	AddComponent<AutoRotate>();
}


BasicCube::~BasicCube() {
}
