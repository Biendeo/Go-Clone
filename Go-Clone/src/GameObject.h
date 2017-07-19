#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

//TODO: Set up children.

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
	/// This should not be called before CreateRootObject(0.
	/// The given type should be a class derived from GameObject. The specifics of a class's construction should be defined in its constructor.
	/// </summary>
	/// <param name="parent">The parent object.</param>
	/// <returns>The constructed object.</returns>
	template<typename T> static std::shared_ptr<T> Create(std::shared_ptr<GameObject> parent) {
		GameObject* newObject = dynamic_cast<GameObject*>(new T(parent));
		if (newObject != nullptr) {
			return std::shared_ptr<T>(newObject->GetSharedPointer());
		} else {
			//? Error here I guess.
			return std::shared_ptr<T>();
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

	private:
	/// <summary>
	/// This is handled internally. Every new object will take this value and increment it by one.
	/// The root object should have ID of 1, and every object should be above it. 0 should not be accessible. If it is, then we've probably overflowed.
	/// </summary>
	static uint32_t nextID;
};