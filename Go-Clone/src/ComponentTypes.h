#pragma once

#include "Component.h"

//? Should I shift this into a .cpp file or just leave it in the header?
/// <summary>
/// All component types inherit from this base class.
/// This just allows for these different types to be individually enabled or disabled (ie. if you want to disable an object's LateUpdate type.
/// </summary>
class ComponentType : public Component {
	public:
	ComponentType(class GameObject* gameObject);

	/// <summary>
	/// Returns whether the current function is active or not.
	/// </summary>
	/// <returns>Whether the current function is active or not.</returns>
	bool IsActive() const;
	
	/// <summary>
	/// Sets the function to be active or not.
	/// </summary>
	/// <param name="active">The new state of the function.</param>
	void SetActive(bool active);

	private:
	/// <summary>
	/// Stores whether the function is active or not.
	/// </summary>
	bool active;
};

/// <summary>
/// Refers to a component that initialises itself at the beginning of the next frame, and not in its constructor. This is useful if multiple objects are created simultaneously.
/// </summary>
class Wakeable : public ComponentType {
	public:
	Wakeable(class GameObject* gameObject);

	/// <summary>
	/// A function that is called when the object is created into the scene. This happens after constructors, but before the updates of the next scene.
	/// </summary>
	virtual void Awake() = 0;
};

/// <summary>
/// Refers to a component that updates over time.
/// </summary>
class Updateable : public ComponentType {
	public:
	Updateable(class GameObject* gameObject);

	/// <summary>
	/// A function that is called once per frame. This doesn't need to be called manually, the engine will handle this for you.
	/// </summary>
	virtual void Update() = 0;
};

/// <summary>
/// Refers to a component that updates over time after regular Updateable objects.
/// </summary>
class LateUpdateable : public ComponentType {
	public:
	LateUpdateable(class GameObject* gameObject);

	/// <summary>
	/// A function that is called once per frame. This version is called after Update, which is useful if anything relies on other objects.
	/// </summary>
	virtual void LateUpdate() = 0;
};

/// <summary>
/// Refers to a component that renders to the screen (and is thus called when rendering the scene graph).
/// </summary>
class Renderable : public ComponentType {
	public:
	Renderable(class GameObject* gameObject);

	/// <summary>
	/// A function that is called specifically to draw something.
	/// </summary>
	virtual void Render() = 0;
};