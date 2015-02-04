#include "Foreach.hpp"
#include "GameObjectManager.h"
#include "System.h"
#include <iostream>

GameObjectDesc root("Root", sf::RectangleShape(),Layer::Root,ComponentType::RenderComponent);
GameObject GameObjectManager::mSceneGraphRoot(root);
//std::map<std::string, GameObject*>	GameObjectManager::sceneLayers;
//std::vector<GameObject*> GameObjectManager::gameLayers;


/*
std::array<int,8> layers = {
							Layer::Background,
							Layer::Default,
							Layer::Enemy,
							Layer::Foreground,
							Layer::Layer,
							Layer::Player,
							Layer::Root,
							Layer::UI 
} ;
*/
std::array<std::string, 8> mLayers =	{
											"Background",
											"Default",
											"Enemy",
											"Foreground",
											"Layer",
											"Player",
											"Root",
											"UI"
										};

std::map<int, std::string> layerMap;


void GameObjectManager::addToLayer(GameObject* gameObject, Layer::Name layer)
{
	/*
	// Loop through the sceneLayers map
	for(std::map<std::string, GameObject*>::iterator itr = sceneLayers.begin(); itr != sceneLayers.end(); ++itr)
	{
		
		// if the name of this layer equals the layer to add to....
		if((*itr).first == layer)
		{
			// push the passed-in game object to that layer's children
			//std::cout << "found layer" << std::endl;
			(*itr).second->mChildren.push_back((gameObject));
			return;
		}
		
		/*std::ostringstream ss;
		ss << layer;
		//std::cout << (*itr).first << std::endl;
		if((*itr).first == ss.str())// && gameObject->mParent == nullptr)
		{
			//(*itr)->addChild(gameObject);
			//gameObject->mParent = (*itr);
			//std::cout << ss.str() << std::endl;
		}
	
	}
	std::cout << "Layer not found" << std::endl;
	*/
}

GameObjectManager::GameObjectManager()
{
	System::init();
	//mSceneGraphRoot = std::unique_ptr<GameObject>(new GameObject(root)).release();
}
void GameObjectManager::init()
{
	createGameObjectGraph(System::mGameObjects);
	/*for(int i = 0; i < mLayers.size(); i++)
	{
		sceneLayers[mLayers[i]] = new GameObject(root);
	}*/
	
}
void GameObjectManager::createGameObjectGraph(std::vector<GameObject*>& gameObjects)
{
	/*
	// pushback game objects to sceneLayers vectors to initialize layer vector
	for(int i = 0; i < mLayers.size(); i++)
	{
		sceneLayers[mLayers[i]] = std::unique_ptr<GameObject>(new GameObject(GameObjectDesc(mLayers[i],sf::RectangleShape(),Layer::Layer))).release();
	}
	
	
	// search all game objects and add them to the correct layer;
	for(std::vector<GameObject*>::iterator object_itr = System::mGameObjects.begin(); object_itr != System::mGameObjects.end(); ++object_itr)
	{
		sceneLayers[(*object_itr)->mLayerName]->mChildren.push_back(*object_itr);
		/*
		const int layerNumber = (*object_itr)->mLayerName;
		
		int j = 0;
		for(std::map<std::string,GameObject*>::iterator map_itr = sceneLayers.begin(); map_itr != sceneLayers.end(); map_itr++)
		{
			if(j == layerNumber)
			{
				(*map_itr).second->mChildren.push_back((*object_itr));
				break;
			}
			j++;
		}
	}

	std::cout << std::endl;
	*/
}

void GameObjectManager::renderSceneGraph(sf::RenderWindow& window)
{
	/*
	for(std::map<std::string, GameObject*>::iterator itr = sceneLayers.begin(); itr != sceneLayers.end(); ++itr)
	{
		if((*itr).second->mName == "second")
		{
			std::cout << "second" << std::endl;
		}
		
		RenderComponent* oRenderComponent = (*itr).second->getRenderComponent();
		if(oRenderComponent != nullptr)
		{	
			oRenderComponent->update();
			oRenderComponent->render(window);
		}

		for(std::vector<GameObject*>::iterator child_itr = (*itr).second->mChildren.begin(); child_itr != (*itr).second->mChildren.end(); ++child_itr)
		{
			//std::cout << (getTransform() * sf::Vector2f()).x << std::endl;
			(*child_itr)->drawSceneGraph(window);
		}

		
	}
	*/

}

//if(mLayerName != Layer::Root && mLayerName != Layer::Layer)
		//std::cout << (getTransform() * sf::Vector2f()).x << " , " << (getTransform() * sf::Vector2f()).y<< std::endl;


/*

// creating 8 layers
		for(std::vector<GameObject*>::iterator itr = System::mGameObjects.begin();
			itr != System::mGameObjects.end(); ++itr)
		{
			if( (*itr)->mParent == nullptr && (*itr)->mLayerName == layers[i] )
			{
				//gameLayers.at(i)->setPosition(0,0);
				gameLayers.at(i)->addChild((*itr));//->addChild(
				//(*itr)->mParent = gameLayers.at(i);
			}
		}

*/