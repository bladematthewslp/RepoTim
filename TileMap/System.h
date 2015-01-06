#pragma once
#include <SFML/Graphics.hpp>
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "LogicComponent.h"
#include "InputComponent.h"
#include "BoxColliderComponent.h"
#include <vector>
#include <iostream>
#include <typeinfo>
#include <queue>
#include <functional>

class GameObjectManager;
struct Grid;

class System
{
public:

	System() { };
	static void init();


	// Component and Game Object containers
	static std::vector<RenderComponent*>	mRenderComponents;
	static std::vector<LogicComponent*>		mLogicComponents;
	static std::vector<InputComponent*>		mInputComponents;
	static std::vector<BoxColliderComponent*>		mBoxColliderComponents;
	static std::vector<GameObject*>			mGameObjects;

	// Command Queue
	static std::queue<std::function<void()>>	mCommandQueue;
	
	// Component management
	template <typename T>
	static void addComponent(T* comp);

	// Game Object Management
	static void									createGameObject(GameObjectDesc desc);
	static GameObject*							findGameObjectByName(std::string name);
	static void									removeGameObject(GameObject* gameObject);
	
	
	// Game loop functions
	static void handleInput(sf::RenderWindow& window, Grid& grid, sf::Event& event);
	static void update(Grid& grid, sf::Time dt, GameObjectManager& gameObjectManager);
	static void render(sf::RenderWindow& window, GameObjectManager& gameObjectManager);
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



