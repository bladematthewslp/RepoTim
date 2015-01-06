#include "GameObject.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "InputComponent.h"
#include "BoxColliderComponent.h"
#include "System.h"
#include "GameObjectManager.h"
#include "PlayerState.h"
#include <iostream>

/*
GameObject::GameObject(sf::RectangleShape shape,  int components, const std::string name)
	: mComponents()
	, mChildren()
	, mRenderComponent(nullptr)
	, mLogicComponent(nullptr)
	, mName(name)
	, mParent(nullptr)
{
	System::mGameObjects.push_back(this);

	HRESULT l_result = CoCreateGuid(&mID);
	//constructComponents(shape, components);
	
}
*/
GameObject::GameObject(GameObjectDesc desc)
	: mComponents()
	, mChildren()
	, mRenderComponent(nullptr)
	, mLogicComponent(nullptr)
	, mBoxColliderComponent(nullptr)
	, mParent(nullptr)
	, mState(nullptr)
{

	constructComponents(desc);
	mName = desc.mName;
	mLayerName = desc.mLayerName;
	HRESULT l_result = CoCreateGuid(&mID);
	if( mLayerName != Layer::Root && mLayerName != Layer::Layer)
	{
		System::mGameObjects.push_back(this);
	}
	
	//GameObjectManager::addToLayer(this, mLayerName);
	
	
	//constructComponents(shape, desc.mComponents);
	//GameObjectManager::addToLayer(this, mLayerName);

}

void GameObject::updateTransforms()
{
		//std::cout << getPosition().x << " , " << getPosition().y << std::endl;

	if(mLayerName != Layer::Layer && mLayerName != Layer::Root && mParent != nullptr && mParent->mLayerName != Layer::Layer)
	{
		GameObjectManager::sceneLayers.find("Y");
		//std::cout << this->mName << std::endl;
		//std::cout << (getTransform().combine(getLocalTransform()).combine(getTransform()) * sf::Vector2f()).x << " , " << (getLocalTransform().combine(getTransform()) * sf::Vector2f()).y << std::endl;
		//std::cout << (getLocalTransform() * getPosition()).x << " , " << (getLocalTransform() * getPosition()).y << std::endl;
		setPosition(getLocalTransform()  * sf::Vector2f() );
	}

	for(std::vector<GameObject*>::iterator itr = mChildren.begin(); itr != mChildren.end(); ++itr)
	{
		(*itr)->updateTransforms();
	}

}

sf::Vector2f GameObject::getLocalPosition()
{
	if(mParent != nullptr)
	{
		return sf::Vector2f(mParent->getPosition() - getPosition());
	}
	else
		return sf::Vector2f();
}

void GameObject::addChild(GameObject* lGameObject)
{
	lGameObject->mParent = this;
	//lGameObject->mLayerName = this->mLayerName;
	mChildren.push_back(lGameObject);

	sf::Transform transform = sf::Transform::Identity;
	//if(updateTransform == true)
	{
		for (const GameObject* node = this; node != nullptr && node->mLayerName != Layer::Layer; node = node->mParent)
			transform = node->getTransform() * transform;
			
		/*for(const GameObject* object = lGameObject; object != nullptr; object = object->mParent)
			transform = object->getTransform() * transform;*/

		//float * zT = const_cast<float* >(transform.getMatrix());
		//zT[14] = 8;
		//sf::Transform transf = sf::Transform::
		//std::cout << zT[14] << std::endl;
		//sf::Transform zT = transform.getMatrix()
		lGameObject->setPosition(transform * sf::Vector2f());
		
	}
	//else
	{
		lGameObject->setPosition(lGameObject->getTransform() * sf::Vector2f());
	}
	
	
}

GameObject* GameObject::findChildByName(std::string lName)
{
	gameObject_vector_itr itr = std::find_if(mChildren.begin(), mChildren.end(), GameObjectComparer(lName));

	if(itr != mChildren.end())
	{
		return *itr;
	}
	else
	{
		return nullptr;
	}
}



sf::Transform	GameObject::getLocalTransform()
{
	return this->mParent->getTransform();
}

sf::Transform	GameObject::getWorldTransform()
{
	sf::Transform transform = sf::Transform::Identity;

	for (const GameObject* node = this; node != nullptr && node->mLayerName != Layer::Layer; node = node->mParent)
		transform = node->getTransform() * transform;

	return transform;

}
sf::Vector2f	GameObject::getWorldPosition()
{
	return getWorldTransform() * sf::Vector2f();
}

void GameObject::drawSceneGraph(sf::RenderWindow& window)
{
	//if(mLayerName != Layer::Root && mLayerName != Layer::Layer)
		//std::cout << (getTransform() * sf::Vector2f()).x << " , " << (getTransform() * sf::Vector2f()).y<< std::endl;
	// render the render component
	if(this->mRenderComponent != nullptr)
	{	
		this->mRenderComponent->update();
		this->mRenderComponent->render(window);
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

		System::addComponent(mBoxColliderComponent);
	}

	if(type & ComponentType::LogicComponent)
	{
		if(script == nullptr)
		{
			mLogicComponent = std::unique_ptr<LogicComponent>(new LogicComponent(this)).release();
			System::addComponent(mLogicComponent);
		}
		else
		{
			mLogicComponent = std::move(dynamic_cast<LogicComponent*>(script));//std::move(script);
			System::addComponent(mLogicComponent);
		}
	}

	if(type & ComponentType::RenderComponent)
	{
		if(script == nullptr)
		{
			mRenderComponent = std::unique_ptr<RenderComponent>(new RenderComponent(this)).release();
			System::addComponent(mRenderComponent);
		}
		else
		{
			mRenderComponent = std::move(dynamic_cast<RenderComponent*>(script));
			System::addComponent(mRenderComponent);
		}
	}

	

	if(type & ComponentType::InputComponent)
	{
		if(script == nullptr)
		{
			mInputComponent = std::unique_ptr<InputComponent>(new InputComponent(this)).release();
			//System::mInputComponents.push_back(mInputComponent);
			System::addComponent(mInputComponent);
		}
		else
		{
			mInputComponent = std::move(dynamic_cast<InputComponent*>(script));
			System::addComponent(mInputComponent);
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

		System::addComponent(mBoxColliderComponent);
	}

	if(desc.mComponentType & ComponentType::LogicComponent)
	{
		if(desc.mComponentScript != nullptr)
		{
			mLogicComponent = std::move(dynamic_cast<LogicComponent*>(desc.mComponentScript));
		}
		else
			mLogicComponent = std::unique_ptr<LogicComponent>(new LogicComponent(this)).release();

		System::addComponent(mLogicComponent);
		
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
		
		System::addComponent(mRenderComponent);
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
/*
void GameObject::addComponent(Component* lComponent)
{
	if(lComponent->mName == "ScriptComponent" || findComponentByName(lComponent->mName) == NULL)
	{
		lComponent->mGameObject = this;
		mComponents.push_back(lComponent);
		lComponent->Start();
	}
	else
	{
	}
}
*/
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
