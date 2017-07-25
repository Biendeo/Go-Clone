#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Component.h"

/// <summary>
/// An object in the current scene graph. Almost everything that exists should inherit from this.
/// </summary>
class GameObject {
	public:
	/// <summary>
	/// Constructs a root object, and returns it. This initialises the engine variable, and the ID counter.
	/// This should only be called by the engine to create the root object, do not call this otherwise.
	/// </summary>
	/// <param name="engine">A pointer to the engine. Should not be nullptr.</param>
	/// <returns>The newly created root object.</returns>
	static std::shared_ptr<GameObject> CreateRootObject(class GoGame* engine);

	/// <summary>
	/// Creates a new GameObject of the given type, and returns it.
	/// This should not be called before CreateRootObject().
	/// The given type should be a class derived from GameObject. The specifics of a class's construction should be defined in its constructor.
	/// </summary>
	/// <returns>The constructed object.</returns>
	template<typename T> static std::shared_ptr<T> Create() {
		static_assert(std::is_base_of<GameObject, T>, "Create does not have a valid GameObject");
		GameObject* newObject = dynamic_cast<GameObject*>(new T());
		if (newObject != nullptr) {
			return std::shared_ptr<T>(newObject->GetSharedPointer());
		} else {
			//? Error here I guess.
			return std::shared_ptr<T>();
		}
	}

	/// <summary>
	/// Creates a new GameObject of the given type, and returns it. The parent is set to the given parent.
	/// This should not be called before CreateRootObject().
	/// The given type should be a class derived from GameObject. The specifics of a class's construction should be defined in its constructor.
	/// </summary>
	/// <param name="parent">The parent object.</param>
	/// <returns>The constructed object.</returns>
	template<typename T> static std::shared_ptr<T> Create(std::shared_ptr<GameObject> parent) {
		static_assert(std::is_base_of<GameObject, T>, "Create does not have a valid GameObject");
		GameObject* newObject = dynamic_cast<GameObject*>(new T(parent));
		if (newObject != nullptr) {
			return std::shared_ptr<T>(newObject->GetSharedPointer());
		} else {
			//? Error here I guess.
			return std::shared_ptr<T>(nullptr);
		}
	}

	~GameObject();

	/// <summary>
	/// Removes this object from the scene. This should clean up any child objects.
	/// </summary>
	void Destroy();

	/// <summary>
	/// Returns the object's ID. This is used to uniquely identify the object.
	/// </summary>
	/// <returns>The object's ID.</returns>
	uint32_t GetID() const;

	/// <summary>
	/// Sets the object's ID and returns it. This should never be called from another object. Only the engine should call it.
	/// </summary>
	/// <param name="newID">The new ID to be set.</param>
	/// <returns>The new ID.</returns>
	uint32_t SetID(uint32_t newID);

	/// <summary>
	/// Returns the object's name.
	/// </summary>
	/// <returns>The object's name.</returns>
	std::string GetName() const;

	/// <summary>
	/// Sets the object's name.
	/// </summary>
	/// <param name="newName">The new name.</param>
	void SetName(const std::string& newName);

	/// <summary>
	/// Returns the object's parent.
	/// </summary>
	/// <returns>The object's parent.</returns>
	std::shared_ptr<GameObject> GetParent() const;

	/// <summary>
	/// Sets the object's parent. This should not be a null object, it must be valid.
	/// </summary>
	/// <param name="newParent">The new parent object.</param>
	void SetParent(std::shared_ptr<GameObject> newParent);

	/// <summary>
	/// Gets a shared pointer of this object. This correctly references the engine, so it should be properly managed.
	/// </summary>
	/// <returns>A shared pointer of this object.</returns>
	std::shared_ptr<GameObject> GetSharedPointer();

	/// <summary>
	/// Gets a vector of all the children of an object. It's much better to iterate over this for some purposes, such as Destroy().
	/// </summary>
	/// <returns>A vector of all the children.</returns>
	std::vector<std::shared_ptr<GameObject>> GetChildren();

	/// <summary>
	/// Returns the first component that matches the given type, or nullptr if no matches.
	/// This will match any subclasses of the given component type, so be specific, or use GetComponents().
	/// </summary>
	/// <returns>The first component that matches the given type, or nullptr if no matches.</returns>
	template<typename T> std::shared_ptr<T> GetComponent() {
		static_assert(std::is_base_of<Component, T>, "GetComponent does not have a valid component");
		for (std::shared_ptr<Component> c : components) {
			if (c->CanCast<T>()) {
				return std::dynamic_pointer_cast<T>(c);
			}
		}
		return std::shared_ptr<T>(nullptr);
	}

	/// <summary>
	/// Returns all the components that match the given type. It'll be empty if there's no matches.
	/// </summary>
	/// <returns>All the components that match the given type, empty if no matches.</returns>
	template<typename T> std::vector<std::shared_ptr<T>> GetComponents() {
		static_assert(std::is_base_of<Component, T>, "GetComponents does not have a valid component");
		std::vector<std::shared_ptr<T>> matchedComponents;
		for (std::shared_ptr<Component> c : components) {
			if (c->CanCast<T>()) {
				matchedComponents.insert(c);
			}
		}
		return matchedComponents;
	}

	/// <summary>
	/// Creates a component and attaches it to this GameObject (or nullptr if it was unable to create (for example, if the component is unique and already exists)).
	/// </summary>
	/// <returns>The component (or nullptr if it wasn't made).</returns>
	template<typename T> std::shared_ptr<T> AddComponent() {
		static_assert(std::is_base_of<Component, T>, "AddComponent does not have a valid component");
		// If a component of the type exists on this object, and it's unique, it won't be made.
		if (GetComponent<T>() != nullptr && T.unique) {
			return std::shared_ptr<T>(nullptr);
		} else {
			std::shared_ptr<T> component = std::shared_ptr<T>(new T());
			components.insert(component);
			return component;
		}
	}

	/// <summary>
	/// Removes the given component from this object.
	/// Do not call this directly; use the component's Destroy() method instead.
	/// </summary>
	/// <param name="component">The component to be removed.</param>
	void RemoveComponent(Component* component);

	protected:
	/// <summary>
	/// Constructs a regular object, and attaches it to the root.
	/// </summary>
	GameObject();

	/// <summary>
	/// Constructs a regular object, and attaches it to the given object. This shouldn't be called publicly, use the 
	/// </summary>
	/// <param name="parent">The object that will become the parent.</param>
	GameObject(std::shared_ptr<GameObject> parent);

	/// <summary>
	/// A pointer to the engine object. This allows the objects to find other parts of data.
	/// It should be passed into the CreateRootObject() function first, and then should never be nullptr.
	/// </summary>
	static class GoGame* engine;

	/// <summary>
	/// The parent object. If the object has no parent, this should be the root object.
	/// If this is the root object, then this should be nullptr.
	/// If it is nullptr and not the root object, or if it is not nullptr and it is, then throw an error ASAP.
	/// </summary>
	std::weak_ptr<GameObject> parent;

	/// <summary>
	/// The object's ID. This uniquely identifies the object in the engine, and allows quick access using hash maps.
	/// It's only really used for metadata, so don't mess with this.
	/// </summary>
	uint32_t ID;

	/// <summary>
	/// The object's name. This is used to identify the object using a human readable string. Multiple objects may have the same name.
	/// </summary>
	std::string name;

	/// <summary>
	/// The object's children. This is used to quickly access all the children of this object.
	/// Do not modify this directly, use the SetParent() function to move the children.
	/// </summary>
	std::map<uint32_t, std::weak_ptr<GameObject>> children;

	/// <summary>
	/// The object's components. GameObjects contain any number of components, and control ownership of them.
	/// Components should be accessed through the helper functions rather than managed here.
	/// </summary>
	std::vector<std::shared_ptr<Component>> components;

	private:
	/// <summary>
	/// This is handled internally. Every new object will take this value and increment it by one.
	/// The root object should have ID of 1, and every object should be above it. 0 should not be accessible. If it is, then we've probably overflowed.
	/// </summary>
	static uint32_t nextID;
};