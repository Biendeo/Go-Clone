#pragma once

#include <memory>
#include <string>

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
	static GameObject* CreateRootObject(class GoGame* engine);

	GameObject();
	GameObject(std::shared_ptr<GameObject> parent);
	~GameObject();

	/// <summary>
	/// Removes this object from the scene. This should clean up any child objects.
	/// </summary>
	/// <param name="object">The object to be destroyed.</param>
	static void Destroy(std::shared_ptr<GameObject> object);

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

	protected:
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

	private:
	/// <summary>
	/// This is handled internally. Every new object will take this value and increment it by one.
	/// The root object should have ID of 1, and every object should be above it. 0 should not be accessible. If it is, then we've probably overflowed.
	/// </summary>
	static uint32_t nextID;
};

