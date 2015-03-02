#pragma once
#include <SFML/Graphics.hpp>
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "LogicComponent.h"
#include "InputComponent.h"
#include "BoxColliderComponent.h"
#include "MusicPlayer.h"
#include "SoundPlayer.h"
#include <array>
#include <vector>
#include <set>
#include <iostream>
#include <typeinfo>
#include <queue>
#include <functional>

//class GameObjectManager;
class World;
struct Grid;

typedef std::unique_ptr<GameObject> Ptr;

class System
{
public:
	static World*											mWorld;
	static MusicPlayer								mMusicPlayer;
	static SoundPlayer								mSoundPlayer;
	
	
	// Scene Graph
	static GameObject								mSceneGraph;
	static std::array<GameObject*, 7>				mSceneLayers;
	// Component and Game Object containers
	static std::vector<RenderComponent*>			mRenderComponents;
	static std::vector<LogicComponent*>				mLogicComponents;
	static std::vector<InputComponent*>				mInputComponents;
	static std::vector<BoxColliderComponent*>		mBoxColliderComponents;
	static std::vector<Ptr>					mGameObjects;

	// Command Queue
	static std::queue<std::function<void()>>	mCommandQueue;
	
	static std::set<GameObject*>					mGameObjsPendingDeletion;

	// ***************
	// FUNCTIONS
	// ***************
	static void										removeAllGameObjects();
	static void										setupSceneGraph();

	System() { };
	static void init(World& world);

	// Component management
	template <typename T>
	static void addComponent(T* comp);

	template <typename T>
	static void removeComponent(T* comp);

	// Game Object Management
	static void									createGameObject(GameObjectDesc desc);
	static GameObject*							findGameObjectByName(std::string name);
	static void									removeGameObject(GameObject* gameObject);
	
	
	// Game loop functions
	static void handleEvent(sf::RenderWindow& window, const sf::Event& event);
	static void handleInput(sf::Event& event);//(sf::RenderWindow& window, Grid& grid, sf::Event& event);
	static void update(Grid& grid, sf::Time dt);//, GameObjectManager& gameObjectManager);
	static void draw(sf::RenderWindow& window);//, GameObjectManager& gameObjectManager);
};


template <typename T>
void System::addComponent(T* comp)
{
	if(dynamic_cast<RenderComponent*>(comp) != nullptr)
	{
		auto newComponent = dynamic_cast<RenderComponent*>(comp);
		System::mRenderComponents.push_back(newComponent);
	}
	else if(dynamic_cast<LogicComponent*>(comp) != nullptr)
	{
		auto newComponent = dynamic_cast<LogicComponent*>(comp);
		System::mLogicComponents.push_back(newComponent);
	}
	else if(dynamic_cast<BoxColliderComponent*>(comp) != nullptr)
	{
		auto newComponent = dynamic_cast<BoxColliderComponent*>(comp);
		System::mBoxColliderComponents.push_back(newComponent);
	}
	else if(dynamic_cast<InputComponent*>(comp) != nullptr)
	{
		std::cout << "Input" << std::endl;
		auto newComponent = dynamic_cast<InputComponent*>(comp);
		System::mInputComponents.push_back(newComponent);
	}
};

template <typename T>
void System::removeComponent(T* comp)
{
	if(dynamic_cast<RenderComponent*>(comp) != nullptr)
	{
		auto newComponent = dynamic_cast<RenderComponent*>(comp);
		System::mRenderComponents.push_back(newComponent);
	}
	else if(dynamic_cast<LogicComponent*>(comp) != nullptr)
	{
		auto newComponent = dynamic_cast<LogicComponent*>(comp);
		System::mLogicComponents.push_back(newComponent);
	}
	else if(dynamic_cast<BoxColliderComponent*>(comp) != nullptr)
	{
		auto newComponent = dynamic_cast<BoxColliderComponent*>(comp);
		System::mBoxColliderComponents.push_back(newComponent);
	}
	else if(dynamic_cast<InputComponent*>(comp) != nullptr)
	{
		std::cout << "Input" << std::endl;
		auto newComponent = dynamic_cast<InputComponent*>(comp);
		System::mInputComponents.push_back(newComponent);
	}
};


