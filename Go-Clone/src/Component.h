#pragma once

#include <memory>

/// <summary>
/// Something that can be attached on to a GameObject. This class itself is abstract and should be extended.
/// Different components can have different properties, so it's important to make sure that components inherit the right properties.
/// </summary>
class Component {
	public:
	Component(class GameObject* gameObject);
	~Component();

	/// <summary>
	/// Destroys the component and removes it from the object it is connected to.
	/// </summary>
	void Destroy();

	/// <summary>
	/// Casts the component to the given type and gives a raw pointer.
	/// This raw pointer can be nullptr if the cast cannot work.
	/// </summary>
	/// <returns>The object in the given type, or nullptr if not possible.</returns>
	template<typename T> T* Cast() {
		return possibleCast = static_cast<T*>(this);
	}

	/// <summary>
	/// Returns whether the component can be casted to the given type or not.
	/// </summary>
	/// <returns>Whether the component can be casted to the given type or not.</returns>
	template<typename T> bool CanCast() {
		return static_cast<T*>(this) != nullptr;
	}

	/// <summary>
	/// Returns the GameObject this component is attached to. This is properly managed by the engine.
	/// </summary>
	/// <returns>The GameObject this component is attached to.</returns>
	std::shared_ptr<GameObject> GetGameObject();

	/// <summary>
	/// This determines whether only one of this component can be on an object at a time or not.
	/// By default, it'll be false (meaning multiple of this component can be on). Simply override this to be true in any subclass.
	/// </summary>
	static const bool unique = false;

	private:
	/// <summary>
	/// Whether the component is currently enabled. Non-active can be accessed and written to, but will globally not run under interfaces.
	/// </summary>
	bool enabled;

	/// <summary>
	/// The GameObject that this component is attached to. Components can't be transferred, so this should always be valid, otherwise just error.
	/// </summary>
	class GameObject* gameObject;
};