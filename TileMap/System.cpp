#include "GameObjectManager.h"
#include "System.h"
#include "Game.h"
#include "Grid.h"
#include "PlayerInput.h"
#include "PlayerLogic.h"
#include "Foreach.hpp"


std::vector<RenderComponent*> System::mRenderComponents;
std::vector<LogicComponent*> System::mLogicComponents;
std::vector<InputComponent*> System::mInputComponents;
std::vector<BoxColliderComponent*> System::mBoxColliderComponents;
std::vector<GameObject*> System::mGameObjects;

std::queue<std::function<void()>> System::mCommandQueue;



void System::init()
{
	mGameObjects.reserve(3000);	
	mLogicComponents.reserve(3000);
	mInputComponents.reserve(3000);
	mRenderComponents.reserve(3000);
	mBoxColliderComponents.reserve(3000);

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
	static int times = 0;
	std::function<void()> func = [=] () 
								{ 
									//std::cout << "FUNCCCCC" << std::endl;
									for(std::vector<GameObject*>::iterator obj_itr = mGameObjects.begin(); obj_itr != mGameObjects.end(); ++obj_itr)
									{
										times ++;
										if(gameObject == (*obj_itr) )
										{
											for(std::vector<RenderComponent*>::iterator ren_itr = mRenderComponents.begin(); ren_itr != mRenderComponents.end(); ++ren_itr)
											{
												if((*obj_itr)->mRenderComponent == (*ren_itr))
												{
													auto mRenderErased = mRenderComponents.erase(std::remove(mRenderComponents.begin(), mRenderComponents.end(), (*ren_itr)),mRenderComponents.end());//mRenderComponents.erase((*obj_itr)->mRenderComponent, (*obj_itr)->mRenderComponent );//(ren_itr));
													(*obj_itr)->mRenderComponent = nullptr;
													break;
												}

											}
											for(std::vector<LogicComponent*>::iterator log_itr = mLogicComponents.begin(); log_itr != mLogicComponents.end(); ++log_itr)
											{
												if((*obj_itr)->mLogicComponent == (*log_itr))
												{
													auto mRenderErased = mLogicComponents.erase(std::remove(mLogicComponents.begin(), mLogicComponents.end(), (*log_itr)),mLogicComponents.end());//mRenderComponents.erase((*obj_itr)->mRenderComponent, (*obj_itr)->mRenderComponent );//(ren_itr));
													(*obj_itr)->mLogicComponent = nullptr;
													break;
												}

											}
											for(std::vector<BoxColliderComponent*>::iterator boxCol_itr = mBoxColliderComponents.begin(); boxCol_itr != mBoxColliderComponents.end(); ++boxCol_itr)
											{
												if((*obj_itr)->mBoxColliderComponent == (*boxCol_itr))
												{
													auto mRenderErased = mBoxColliderComponents.erase(std::remove(mBoxColliderComponents.begin(), mBoxColliderComponents.end(), (*boxCol_itr)),mBoxColliderComponents.end());//mRenderComponents.erase((*obj_itr)->mRenderComponent, (*obj_itr)->mRenderComponent );//(ren_itr));
													(*obj_itr)->mBoxColliderComponent = nullptr;
													break;
												}

											}
											mGameObjects.erase(std::remove(mGameObjects.begin(), mGameObjects.end(), (*obj_itr)), mGameObjects.end());

											break;
										}

										
									}
								};
	
	mCommandQueue.push(func);
	
}

GameObject*	System::findGameObjectByName(std::string name)
{
	std::vector<GameObject*>::iterator itr;
	for( itr = mGameObjects.begin(); itr != mGameObjects.end(); ++itr)
	{
		if((*itr)->mName == name)
		{
			break;
		}
	}
	if(itr == mGameObjects.end())
	{
		return nullptr;
	}
	else
		return *itr;
}



void System::handleInput(sf::RenderWindow& window, Grid& grid, sf::Event& event)
{
	// handle events
	while(window.pollEvent(event))
	{

		for(std::vector<InputComponent*>::iterator iter = mInputComponents.begin(); iter != mInputComponents.end(); ++iter)
		{
			//(*iter)->handleEvents(event);
			dynamic_cast<PlayerInput*>(*iter)->handleEvents(grid, event);
		}
	}

	// handle real time input
	for(std::vector<InputComponent*>::iterator iter = mInputComponents.begin(); iter != mInputComponents.end(); ++iter)
	{
		//dynamic_cast<PlayerInput*>(*iter);
		dynamic_cast<PlayerInput*>(*iter)->handleRealtimeInput(grid, event);//(event);
	}


	if(event.type == sf::Event::Closed)
			window.close();
}


void System::update(Grid& grid, sf::Time dt, GameObjectManager& system)
{
	//for(std::queue<std::function<void()>>::
	for(int i = 0; i < mCommandQueue.size(); i++)
	{
		auto command = mCommandQueue.front();
		command();
		mCommandQueue.pop();
		
	}
	// cheap way of updating the transform component (that is inherently derived from sf::Transformable	)
	for(std::vector<GameObject*>::iterator iter = mGameObjects.begin(); iter != mGameObjects.end(); ++iter)
	{
		(*iter)->updateTransforms();
	}

	// update logic component
	for(std::vector<LogicComponent*>::iterator iter = mLogicComponents.begin(); iter != mLogicComponents.end(); ++iter)
	{
		int size = mLogicComponents.size();
		PlayerLogic* itr = dynamic_cast<PlayerLogic*>(*iter);
		if(itr != nullptr)
			itr->update(grid);
		else if (itr == nullptr)
			(*iter)->update();

		//if(mLogicComponents.size() != size)
			//break;
	}

	for(std::vector<BoxColliderComponent*>::iterator iter = mBoxColliderComponents.begin(); iter!= mBoxColliderComponents.end(); ++iter)
	{
		(*iter)->update();
	}
}

void System::render(sf::RenderWindow& window, GameObjectManager& gameObjectManager)
{
	GameObjectManager::renderSceneGraph(window);
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

