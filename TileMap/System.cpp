//#include "GameObjectManager.h"
#include "System.h"
//#include "Game.h"
//#include "Grid.h"
#include "PlayerInput.h"
//#include "PlayerLogic.h"
#include "Foreach.hpp"



std::array<GameObject*, 7>				System::mSceneLayers;
std::vector<RenderComponent*>			System::mRenderComponents;
std::vector<LogicComponent*>			System::mLogicComponents;
std::vector<InputComponent*>			System::mInputComponents;
std::vector<BoxColliderComponent*>		System::mBoxColliderComponents;
std::vector<Ptr>						System::mGameObjects;

std::queue<std::function<void()>>		System::mCommandQueue;
std::set<GameObject*>					System::mGameObjsPendingDeletion;

GameObjectDesc							sceneGraphDesc("Root",sf::RectangleShape(), Layer::Root);
GameObject								System::mSceneGraph(sceneGraphDesc);

void System::init()
{
	mGameObjects.reserve(3000);	
	mLogicComponents.reserve(3000);
	mInputComponents.reserve(3000);
	mRenderComponents.reserve(3000);
	mBoxColliderComponents.reserve(3000);

	GameObjectDesc layers[] = 
	{
		//GameObjectDesc("Root",			sf::RectangleShape(),Layer::Layer),
		GameObjectDesc("Layer",			sf::RectangleShape(),Layer::Layer),
		GameObjectDesc("Background",	sf::RectangleShape(),Layer::Layer),
		GameObjectDesc("Enemy",			sf::RectangleShape(),Layer::Layer),
		GameObjectDesc("Default",		sf::RectangleShape(),Layer::Layer),
		GameObjectDesc("Player",		sf::RectangleShape(),Layer::Layer),
		GameObjectDesc("Foreground",	sf::RectangleShape(),Layer::Layer),
		GameObjectDesc("UI",			sf::RectangleShape(),Layer::Layer),
	
	};
	
	// initialize the different layers
	for(int i = 0; i < 7; ++i)
	{
		std::unique_ptr<GameObject> layer(new GameObject(layers[i], true));
		
		mSceneGraph.addChild(layer.get());
		mSceneLayers[i] = std::move(layer.release());
		//mGameObjects.push_back();
		//mSceneGraph.addChild(std::move(layer));
	}
	/*
	for(int i = 0; i < mGameObjects.size(); i++)
	{
		for(int j = 0; j < mSceneLayers.size(); j++)
		{
			if(mGameObjects[i]->mLayerName == mSceneLayers[j]->mName)
			{
				
				mSceneLayers[j]->addChild(std::unique_ptr<GameObject>(mGameObjects[i]));
			}
		}
	}
	*/
	//std::unique_ptr<GameObject> layer(new GameObject());
	
	
	std::cout << "DONE INITIALIZATING SYSTEM" << std::endl;
}

void System::setupSceneGraph()
{

}

//void System::pushCommand(std::function<

void System::createGameObject(GameObjectDesc desc)
{
	std::function<void()> func = [=] () 
								{ 
									//std::cout << "FUNCCCCC" << std::endl;
									GameObject* ob = std::unique_ptr<GameObject>(new GameObject(desc)).release();
								};
	//func();
	mCommandQueue.push(func);
	//GameObject* gameObject = std::unique_ptr<GameObject>(new GameObject(desc)).release();
	
}

void System::removeGameObject(GameObject* gameObject)
{
	if(!gameObject)
		return;

	// add object to set of objects pending deleting
	mGameObjsPendingDeletion.insert(gameObject);

	std::function<void()> func = [=] () 
								{ 
									if(!gameObject)
										return;
									
									while(mGameObjsPendingDeletion.size() > 0)
									{
										
										(*mGameObjsPendingDeletion.begin())->Destroy();
										mGameObjsPendingDeletion.erase(mGameObjsPendingDeletion.begin());
									}
								};
	

	mCommandQueue.push(func);
	
}

GameObject*	System::findGameObjectByName(std::string name)
{
	std::vector<Ptr>::iterator itr;
	for( itr = mGameObjects.begin(); itr != mGameObjects.end(); ++itr)
	{
		if((*itr)->mName == name && (*itr)->mLayerName != Layer::Root && (*itr)->mLayerName != Layer::Layer)
		{
			break;
		}
	}
	if(itr == mGameObjects.end())
	{
		return nullptr;
	}
	else
		return itr->get();
}



void System::handleEvent(sf::RenderWindow& window, const sf::Event& event) //(sf::RenderWindow& window, Grid& grid, sf::Event& event)
{
//	std::cout << "SYSTEM HANDLE INPUT!" << std::endl;
	
	// handle events
	//while(window.pollEvent(event))
	
	for(std::vector<InputComponent*>::iterator iter = mInputComponents.begin(); iter != mInputComponents.end(); ++iter)
	{
		(*iter)->handleEvents(event);
		
		//dynamic_cast<PlayerInput*>(*iter)->handleEvents(event);
	}
	
}

void System::handleInput(sf::Event& event)
{
	// handle real time input
	for(std::vector<InputComponent*>::iterator iter = mInputComponents.begin(); iter != mInputComponents.end(); ++iter)
	{
		//dynamic_cast<PlayerInput*>(*iter)->handleRealtimeInput(event);//(event);
		(*iter)->handleRealtimeInput(event);
	}
}


void System::update(Grid& grid, sf::Time dt)//, GameObjectManager& system)
{
	
	// PROCESS WAITING COMMANDS
	for(int i = 0; i < mCommandQueue.size(); i++)
	{
		auto command = mCommandQueue.front();
		command();
		mCommandQueue.pop();
		
	}
	//std::cout << mGameObjects.size() << std::endl;
	// cheap way of updating the transform component (that is inherently derived from sf::Transformable	)
	for(std::vector<Ptr>::iterator iter = mGameObjects.begin(); iter != mGameObjects.end(); ++iter)
	{
		(*iter)->updateTransforms();
	}


	// update logic component
	for(std::vector<LogicComponent*>::iterator iter = mLogicComponents.begin(); iter != mLogicComponents.end(); ++iter)
	{
		int size = mLogicComponents.size();
		
		//PlayerLogic* itr = dynamic_cast<PlayerLogic*>(*iter);
		//if(itr != nullptr)
		//	itr->update(grid);
		//else if (itr == nullptr)
			(*iter)->update(grid);

		//if(mLogicComponents.size() != size)
			//break;
	}
	// ********************
	// BOX COLLIDER
	// ********************

	// 1.) First update the positions for all box colliders
	for(std::vector<BoxColliderComponent*>::iterator iter = mBoxColliderComponents.begin(); iter!= mBoxColliderComponents.end(); ++iter)
	{
		(*iter)->update();
		//if( (*iter)->mGameObject->mName == "Player")
		//	(*iter)->onCollisionEnter(grid);
	}

	// 2.) Next, handle collision for box colliders
	for(std::vector<BoxColliderComponent*>::iterator iter_this = mBoxColliderComponents.begin(); iter_this!= mBoxColliderComponents.end(); ++iter_this)
	{
		// check if each collider in this collider's set of mColliders are still intersecting. 
		std::set<BoxColliderComponent*> collidersToRemove;
		
		for(std::set<BoxColliderComponent*>::iterator iter_col = (*iter_this)->mColliders.begin();
				iter_col != (*iter_this)->mColliders.end();
				++iter_col)
		{
			
			// If is deleted or no longer intersecting...
			if( (*iter_col)->mDeleted == true
				|| !(*iter_this)->getCollisionBox()->getGlobalBounds().intersects((*iter_col)->getCollisionBox()->getGlobalBounds()))
			{
				// ...call this collider's OnCollisionExit(), passing in the collider that is no longer touching...
				// if deleted, it will not call onCollisionExit()
				if((*iter_col)->mDeleted != true)
					(*iter_this)->onCollisionExit(grid, (*iter_col));
				

				// copy a pointer to this collider to the collidersToRemove vector to be removed outside this for-loop
				collidersToRemove.insert(*iter_col);
			}
			
		}

		// ...and remove collider from mColliders
		while(collidersToRemove.size() != 0)
		{
			(*iter_this)->mColliders.erase(*(collidersToRemove.begin()));
			collidersToRemove.erase(collidersToRemove.begin());
		}

		// if there are any remaining colliders still in the mColliders set, call OnCollisionStay() on this collider
 		FOREACH(auto iter_col, (*iter_this)->mColliders)
		{
			(*iter_this)->onCollisionStay(grid, iter_col);
		}
	
		
		// Now check if there are any new collisions since last frame
		for(std::vector<BoxColliderComponent*>::iterator iter_other = mBoxColliderComponents.begin(); iter_other!= mBoxColliderComponents.end(); ++iter_other)
		{
			BoxColliderComponent* other = (*iter_other);//->getCollisionBox();

			//Check if the two colliders are not the same and if they are intersecting
			if((*iter_this) != (*iter_other) 
				&& (*iter_this)->getCollisionBox()->getGlobalBounds().intersects(other->getCollisionBox()->getGlobalBounds()))
			{
				// check if the size changes between the insert() call...
				int beforeSize = (*iter_this)->mColliders.size();
				(*iter_this)->mColliders.insert(other);
				int afterSize = (*iter_this)->mColliders.size();
				
				// ... if so, call the onCollisionEnter() function
				if(beforeSize != afterSize)
				{
					// Call outer-loop collider's OnCollisionEnter, passing the inner-loop collider
				(*iter_this)->onCollisionEnter(grid, other);
				}
				
				
			
				
			}

		}
	}
	
}

void System::draw(sf::RenderWindow& window)//, GameObjectManager& gameObjectManager)
{
	for(std::array<GameObject*, 7>::iterator iter = mSceneLayers.begin(); iter != mSceneLayers.end(); ++iter)
	{
		GameObject* gameObject = (*iter);
		RenderComponent* renderComponent = (*iter)->mRenderComponent;
		if(renderComponent != nullptr)
		{
			renderComponent->update(window);
			renderComponent->draw(window, sf::RenderStates::Default);
		}

		for(std::vector<GameObject*>::iterator child_itr = gameObject->mChildren.begin(); child_itr != gameObject->mChildren.end(); ++child_itr)
		{
			//std::cout << (getTransform() * sf::Vector2f()).x << std::endl;
			(*child_itr)->drawSceneGraph(window);
		}
	}/*
	for(std::vector<RenderComponent*>::iterator iter = mRenderComponents.begin(); iter != mRenderComponents.end(); ++iter)
	{
		(*iter)->update();
		(*iter)->draw(window, sf::RenderStates::Default);
	}*/
	//GameObjectManager::renderSceneGraph(window);
	//gameObjectManager.mSceneGraphRoot.drawSceneGraph(window);//draw(window, sf::RenderStates::Default);

	/*
	for(std::vector<RenderComponent*>::iterator iter = mRenderComponents.begin(); iter != mRenderComponents.end(); ++iter)
	{
		if((*iter)->mGameObject->mLayerName == Layer::Default)
		{
			(*iter)->update();
			(*iter)->draw(window, sf::RenderStates::Default);
		}
	}

	for(std::vector<RenderComponent*>::iterator iter = mRenderComponents.begin(); iter != mRenderComponents.end(); ++iter)
	{
		if((*iter)->mGameObject->mLayerName == Layer::Player)
		{
			(*iter)->update();
			(*iter)->draw(window, sf::RenderStates::Default);
		}
	}
	*/
}

