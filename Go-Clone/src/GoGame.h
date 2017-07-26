#pragma once

#include <map>
#include <queue>
#include <SFML/Window.hpp>

#include "ComponentTypes.h"
#include "GameState.h"
#include "GameObject.h"
#include "Input.h"

/// <summary>
/// Stores information about the current system, this is mostly used for window management and hardware polling.
/// </summary>
struct SystemVariables {
	bool fullscreen;
	sf::Uint32 windowWidth;
	sf::Uint32 windowHeight;
	sf::Uint32 screenWidth;
	sf::Uint32 screenHeight;
	const std::string windowTitle = "Go Game";
};

/// <summary>
/// The main class of the game. This should be made immediately in main, and arguments should be passed to it.
/// </summary>
class GoGame {
	public:
	GoGame();
	~GoGame();

	/// <summary>
	/// Starts the game. This should be called immediately after construction.
	/// </summary>
	void Start();

	/// <summary>
	/// Returns the game state object for classes to refer to.
	/// </summary>
	const GameState& GetGameState() const;

	/// <summary>
	/// Switches the program to and from fullscreen.
	/// </summary>
	/// <returns>Whether the program is now fullscreen or not.</returns>
	bool ToggleFullscreen();

	/// <summary>
	/// Returns the root game object in the scene.
	/// </summary>
	/// <returns>The root game object in the scene.</returns>
	std::shared_ptr<GameObject> GetRootObject();

	/// <summary>
	/// Registers an object into the list of objects.
	/// Do not call this from anywhere except from the GameObject instantiation.
	/// If the new object's ID exists already, we have a problem, so it'll probably error here.
	/// </summary>
	/// <param name="object">The object to be registered.</param>
	void RegisterObject(std::shared_ptr<GameObject> object);

	/// <summary>
	/// Unregisters an object from the list of objects.
	/// Do not call this from anywhere except from the GameObject destroy function.
	/// If the object's ID doesn't exist, then we'll probably error here.
	/// </summary>
	/// <param name="object">The object to be unregistered.</param>
	void UnregisterObject(std::shared_ptr<GameObject> object);

	/// <summary>
	/// Gets a shared pointer of a given object. This is so that they correctly reference the original shared pointer.
	/// </summary>
	/// <param name="ID">The ID of the object.</param>
	/// <returns>A shared pointer of the object.</returns>
	std::shared_ptr<GameObject> GetSharedPointer(uint32_t ID);

	/// <summary>
	/// Gets a constant version of the Input object. This is useful for objects to determine input logic themselves.
	/// </summary>
	/// <returns>A constant version of the Input object.</returns>
	const Input& GetInput() const;

	/// <summary>
	/// Adds the object to the awake queue for the next frame. This doesn't need to be called manually.
	/// </summary>
	/// <param name="wakableComponent">The component that will be woken up.</param>
	void AddToAwakeQueue(std::shared_ptr<Wakeable> wakableComponent);

	private:
	/// <summary>
	/// Renders the current game scene. This should only be called in the game loop.
	/// </summary>
	void RenderScene();

	/// <summary>
	/// Initialises all objects that are in the awake queue.
	/// </summary>
	void Awake();

	/// <summary>
	/// Updates all objects in the scene.
	/// </summary>
	void Update();

	/// <summary>
	/// Updates all objects in the scene after Update.
	/// </summary>
	void LateUpdate();

	/// <summary>
	/// Contains every object in the scene. Shared pointers are used since this has ownership of them.
	/// </summary>
	std::map<uint32_t, std::shared_ptr<GameObject>> objects;
	
	/// <summary>
	/// The root object is special and is held on it's own.
	/// All objects in the scene must be children of this object. All game loop items depend on it.
	/// </summary>
	std::weak_ptr<GameObject> root;

	/// <summary>
	/// This tracks all the components that need to wake up before the next frame. It should be emptied after the Awake function.
	/// </summary>
	std::queue<std::weak_ptr<Wakeable>> awakeQueue;

	//TODO: Add a camera object here.

	/// <summary>
	/// This contains all the variables related to defining the current variables for the game.
	/// </summary>
	GameState gameState;

	//? Should I be using a smart pointer here?
	/// <summary>
	/// The current rendering window. This is reset whenever the window switches from fullscreen to windowed.
	/// </summary>
	sf::Window* window;

	/// <summary>
	/// The system variables, particularly for window management and hardware polling. Game specific variables should not be here.
	/// </summary>
	SystemVariables systemVars;

	/// <summary>
	/// Handles all the user-level input of the engine. Inputs are either handled here, or spit back out (which means they're engine related).
	/// </summary>
	Input input;
};