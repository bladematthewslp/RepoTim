#include "GameObject.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "InputComponent.h"
#include "BoxColliderComponent.h"
#include "System.h"
#include "Foreach.hpp"
//#include "GameObjectManager.h"
#include "CState.h"
#include <iostream>

int GameObject::GameObjectCounter = 0;

GameObject::GameObject(GameObjectDesc desc, bool isInitializing)
	: mComponents()
	, mChildren()
	, mRenderComponent(nullptr)
	, mLogicComponent(nullptr)
	, mBoxColliderComponent(nullptr)
	, mInputComponent(nullptr)
	, mParent(nullptr)
	, mState(nullptr)
	, mChildPosition(0,0)
{
	static int GameObjectCount = 0;
	
	mChildren.reserve(300);

	constructComponents(desc);
	mName = desc.mName;
	mLayerName = desc.mLayerName;
	HRESULT l_result = CoCreateGuid(&mID);


	// add to sceneLayers
	if(mLayerName != Layer::Root && mLayerName != Layer::Layer)
	{
		for(int j = 0; j < System::mSceneLayers.size(); j++)
		{
			if(System::mSceneLayers[j]->mName == mLayerName)
			{
				
				System::mSceneLayers[j]->addChild(this);
				break;
			}
		}
	}

	// move ownership to System::mGameObjects vector
	if( mLayerName != Layer::Root && mLayerName != Layer::Layer)
	{
		System::mGameObjects.push_back(std::move(std::unique_ptr<GameObject>(this)));
	}
	GameObjectCount++;
	//std::cout << ++GameObjectCounter << std::endl;
}

void GameObject::addChild(GameObject* child)
{

	//if(child->mParent->mName != Layer::Root)


	//if child does not have a parent
		// add code here

	//if child has a parent
	if(child->mParent != nullptr)
	{
		// if the parent is a layer
		
		/*if(child->mParent->mLayerName == Layer::Layer)
		{
			for(std::array<GameObject*, 7>::iterator layer_itr = System::mSceneLayers.begin();
				layer_itr != System::mSceneLayers.end();
				++layer_itr)
			{
				if((*layer_itr)->mLayerName == Layer::Layer)
				{
					std::vector<GameObject*>::iterator itr = std::remove((*layer_itr)->mChildren.begin(), (*layer_itr)->mChildren.end(), child);
					(*layer_itr)->mChildren.erase(itr, (*layer_itr)->mChildren.end());

				}

			}
		}
		else*/
		{
			std::vector<GameObject*>::iterator itr = std::remove(child->mParent->mChildren.begin(), child->mParent->mChildren.end(), child);
			child->mParent->mChildren.erase(itr, child->mParent->mChildren.end());
		}
	}

	mChildren.push_back(child);
	child->mParent = this;
	child->mChildPosition = child->getPosition();
	child->setPosition(child->mParent->getTransform() * child->mChildPosition);

	/*
	GameObject* temp = child.get();
	mChildren.push_back(std::move(child));
	temp->mParent = this;
	temp->mChildPosition = temp->getPosition();
	temp->setPosition(temp->mParent->getTransform()  * temp->mChildPosition );
	*/
	
}

GameObject::~GameObject()
{
	
	

}
void GameObject::updateTransforms()
{
	if(mLayerName == Layer::Layer || mLayerName == Layer::Root)
		return;
	if(mLayerName != Layer::Layer && mLayerName != Layer::Root && mParent != nullptr && mParent->mLayerName != Layer::Layer)
	{
		//setPosition(getLocalTransform()  * sf::Vector2f() );

		setPosition(this->mParent->getTransform()  * mChildPosition );

	}
	
	for(std::vector<GameObject*>::iterator itr = mChildren.begin(); itr != mChildren.end(); ++itr)
	{
		(*itr)->updateTransforms();
	}
	
}

void GameObject::setChildPosition(float x, float y)
{
	mChildPosition.x = x;
	mChildPosition.y = y;
}



void	GameObject::moveChild(float x, float y)
{
	mChildPosition.x += x;
	mChildPosition.y += y;
}
void	GameObject::moveChild(sf::Vector2f vec)
{
	mChildPosition.x += vec.x;
	mChildPosition.y += vec.y;
}

sf::Vector2f GameObject::getLocalPosition()
{
	if(mParent->mLayerName == Layer::Layer) // if it has no parent game object
	{
		return getPosition();
		//return sf::Vector2f(mParent->getPosition() - getPosition());
	}
	else	// if it had a parent game object...
	{
			// return the mChildPosition variable
		return mChildPosition;
		//return sf::Vector2f();
	}
}

sf::Vector2f GameObject::getWorldPosition()
{
	sf::Vector2f position;
	if(mParent->mLayerName == Layer::Layer)
	{
		position = getPosition();
	}
	else
	{
		position = mParent->getTransform() * mChildPosition;
	}
	return position;
}



GameObject* GameObject::findChildByName(std::string lName)
{
	/*
	gameObject_vector_itr itr = std::find_if(mChildren.begin(), mChildren.end(), GameObjectComparer(lName));

	if(itr != mChildren.end())
	{
		return *itr;
	}
	else
	{
		return nullptr;
	}
	*/
	return nullptr;
}



sf::Transform	GameObject::getLocalTransform()
{
	return this->mParent->getTransform() * getTransform();
}

sf::Transform	GameObject::getWorldTransform()
{
	sf::Transform transform = sf::Transform::Identity;

	for (const GameObject* node = this; node != nullptr && node->mLayerName != Layer::Layer; node = node->mParent)
		transform = node->getTransform() * transform;

	return transform;

}



void GameObject::drawSceneGraph(sf::RenderWindow& window)
{
	
	//if(mLayerName != Layer::Root && mLayerName != Layer::Layer)
		//std::cout << (getTransform() * sf::Vector2f()).x << " , " << (getTransform() * sf::Vector2f()).y<< std::endl;
	// render the render component
	if(this->mRenderComponent != nullptr)
	{	
		this->mRenderComponent->update(window);
		this->mRenderComponent->draw(window);
	}

	//render the box collider if it exists
	if(this->mBoxColliderComponent != nullptr)
	{
		mBoxColliderComponent->render(window);
	}
	for(std::vector<GameObject*>::iterator itr = mChildren.begin(); itr != mChildren.end(); ++itr)
	{
		//std::cout << (getTransform() * sf::Vector2f()).x << std::endl;
		(*itr)->drawSceneGraph(window);
	}
}




void GameObject::addComponent(ComponentType::type type, Component* script)
{
	if(type & ComponentType::TransformComponent)
	{
	}

	if(type & ComponentType::BoxColliderComponent)
	{
		if(script == nullptr)
		{
			mBoxColliderComponent = std::unique_ptr<BoxColliderComponent>(new BoxColliderComponent(this)).release();
			
		}
		else
		{
			mBoxColliderComponent = std::move(dynamic_cast<BoxColliderComponent*>(script));
		}

		//System::addComponent(mBoxColliderComponent);
	}

	if(type & ComponentType::LogicComponent)
	{
		if(script == nullptr)
		{
			mLogicComponent = std::unique_ptr<LogicComponent>(new LogicComponent(this)).release();
			//System::addComponent(mLogicComponent);
		}
		else
		{
			mLogicComponent = std::move(dynamic_cast<LogicComponent*>(script));//std::move(script);
			//System::addComponent(mLogicComponent);
		}
	}

	if(type & ComponentType::RenderComponent)
	{
		if(script == nullptr)
		{
			mRenderComponent = std::unique_ptr<RenderComponent>(new RenderComponent(this)).release();
			//System::addComponent(mRenderComponent);
		}
		else
		{
			mRenderComponent = std::move(dynamic_cast<RenderComponent*>(script));
			//System::addComponent(mRenderComponent);
		}
	}

	

	if(type & ComponentType::InputComponent)
	{
		if(script == nullptr)
		{
			mInputComponent = std::unique_ptr<InputComponent>(new InputComponent(this)).release();
			//System::mInputComponents.push_back(mInputComponent);
			//System::addComponent(mInputComponent);
		}
		else
		{
			mInputComponent = std::move(dynamic_cast<InputComponent*>(script));
			//System::addComponent(mInputComponent);
		}
		
	};
}

void GameObject::Awake()
{
}

void GameObject::create()
{

}
void GameObject::Destroy()
{
	// delete all components
	if(mLogicComponent != nullptr)
	{
		mLogicComponent->~LogicComponent();
		mLogicComponent = nullptr;
	}

	if(mRenderComponent != nullptr)
	{
		mRenderComponent->~RenderComponent();
		mRenderComponent = nullptr;
	}

	if(mBoxColliderComponent != nullptr)
	{
		mBoxColliderComponent->~BoxColliderComponent();
		mBoxColliderComponent = nullptr;
	}

	if(mInputComponent != nullptr)
	{
		mInputComponent->~InputComponent();
		mInputComponent = nullptr;
	}
	
	// remove object from scene graph (remove from parent object's list of children)
	if(mParent != nullptr)
	{
		std::vector<GameObject*>::iterator itr = std::remove(mParent->mChildren.begin(), mParent->mChildren.end(), this);
		mParent->mChildren.erase(itr, mParent->mChildren.end());
	}

	// if object has children, call Destroy() on those as well
	while(mChildren.size() != 0)
	{
		std::vector<GameObject*>::iterator itr = mChildren.begin();
		(*itr)->Destroy();
	}

	for(std::vector<Ptr>::iterator obj_itr = System::mGameObjects.begin(); obj_itr != System::mGameObjects.end(); obj_itr++)
	{
		if( (*obj_itr)->mID.Data1 == mID.Data1)
		{
			System::mGameObjects.erase(obj_itr);
			break;
		}
	}

	
	
}
void GameObject::FixedUpdate()
{
}

void GameObject::LateUpdate()
{
}
void GameObject::Start()
{
}

void GameObject::Update()
{
}

void GameObject::constructComponents(GameObjectDesc& desc)
{
	if(desc.mComponentType & ComponentType::TransformComponent)
	{
	}
	

	if(desc.mComponentType & ComponentType::BoxColliderComponent)
	{
		if(desc.mComponentScript != nullptr)
		{
			mBoxColliderComponent = std::move(dynamic_cast<BoxColliderComponent*>(desc.mComponentScript));
		}
		else
		{
			mBoxColliderComponent = std::unique_ptr<BoxColliderComponent>(new BoxColliderComponent(this)).release();
		}

		//System::addComponent(mBoxColliderComponent);
	}

	if(desc.mComponentType & ComponentType::LogicComponent)
	{
		if(desc.mComponentScript != nullptr)
		{
			mLogicComponent = std::move(dynamic_cast<LogicComponent*>(desc.mComponentScript));
		}
		else
			mLogicComponent = std::unique_ptr<LogicComponent>(new LogicComponent(this)).release();

		//System::addComponent(mLogicComponent);
		
	}

	if(desc.mComponentType & ComponentType::RenderComponent)
	{
		if(desc.mComponentScript != nullptr)
		{
			mRenderComponent = std::move(dynamic_cast<RenderComponent*>(desc.mComponentScript));
		}
		else
			mRenderComponent = std::unique_ptr<RenderComponent>(new RenderComponent(this)).release();
		
		mRenderComponent->mSprite = desc.mSprite;
		//mRenderComponent->mSprite = shape;
		
		//System::addComponent(mRenderComponent);
	}

	

	if(desc.mComponentType & ComponentType::InputComponent)
	{
	}
}


RenderComponent* GameObject::getRenderComponent()
{
	return mRenderComponent;
}

sf::RectangleShape*	GameObject::getSprite()
{
	return &mRenderComponent->mSprite;
}

void GameObject::addComponent(Component* newComponent)
{
	//mRenderComponent = newComponent;

}

Component* GameObject::findComponentByName(std::string lName)
{
	component_vector_itr itr = std::find_if(mComponents.begin(), mComponents.end(), ComponentComparer(lName));

	if(itr != mComponents.end())
	{
		return *itr;
	}
	else
	{
		return nullptr;
	}
}
