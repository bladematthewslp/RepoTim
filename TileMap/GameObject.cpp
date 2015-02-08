#include "GameObject.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "InputComponent.h"
#include "BoxColliderComponent.h"
#include "System.h"
//#include "GameObjectManager.h"
#include "CState.h"
#include <iostream>



GameObject::GameObject(GameObjectDesc desc, bool isInitializing)
	: mComponents()
	, mChildren()
	, mRenderComponent(nullptr)
	, mLogicComponent(nullptr)
	, mBoxColliderComponent(nullptr)
	, mParent(nullptr)
	, mState(nullptr)
	, mChildPosition(0,0)
{
	static int GameObjectCount = 0;
	
	constructComponents(desc);
	mName = desc.mName;
	mLayerName = desc.mLayerName;
	HRESULT l_result = CoCreateGuid(&mID);
	if( mLayerName != Layer::Root && mLayerName != Layer::Layer)
	{
		System::mGameObjects.push_back(this);
	}
	/*
	if( mLayerName == Layer::Root )
	{
		System::mSceneLayers[GameObjectCount] = this;
		return;
	}

	if( isInitializing != true )
	{
		if(mLayerName == Layer::Layer)
		{
			System::mSceneLayers[GameObjectCount] = this;
		}
	}
	*/
	
	if(mLayerName != Layer::Layer && mLayerName != Layer::Root)
	{
		for(int j = 0; j < System::mSceneLayers.size(); j++)
		{
			if(System::mSceneLayers[j]->mName == mLayerName)
			{
				
				System::mSceneLayers[j]->addChild(std::move(std::unique_ptr<GameObject>(this)));
				break;
			}
		}
	}

	GameObjectCount++;
}

GameObject::~GameObject()
{
	
}
void GameObject::updateTransforms()
{
	if(mLayerName != Layer::Layer && mLayerName != Layer::Root && mParent != nullptr && mParent->mLayerName != Layer::Layer)
	{
		//setPosition(getLocalTransform()  * sf::Vector2f() );

		setPosition(this->mParent->getTransform()  * mChildPosition );

	}
	
	for(std::vector<Ptr>::iterator itr = mChildren.begin(); itr != mChildren.end(); ++itr)
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

void GameObject::addChild(Ptr child)
{
	GameObject* temp = child.get();
	mChildren.push_back(std::move(child));
	temp->mParent = this;
	temp->mChildPosition = temp->getPosition();
	temp->setPosition(temp->mParent->getTransform()  * temp->mChildPosition );
	/*
	//lGameObject->mLayerName = this->mLayerName;
	

	sf::Transform transform = sf::Transform::Identity;
	//if(updateTransform == true)
	{
		for (const GameObject* node = this; node != nullptr && node->mLayerName != Layer::Root && node->mLayerName != Layer::Layer; node = node->mParent)
			transform = node->getTransform() * transform;
			
		/*for(const GameObject* object = lGameObject; object != nullptr; object = object->mParent)
			transform = object->getTransform() * transform;

		//float * zT = const_cast<float* >(transform.getMatrix());
		//zT[14] = 8;
		//sf::Transform transf = sf::Transform::
		//std::cout << zT[14] << std::endl;
		//sf::Transform zT = transform.getMatrix()
		//std::cout << temp->getPosition().x << "," << temp->getPosition().y << std::endl;

		//temp->setPosition(transform * sf::Vector2f());
		//std::cout << temp->getPosition().x << "," << temp->getPosition().y << std::endl;

		
	}
	//else
	{
		//temp->setPosition(temp->getTransform() * sf::Vector2f());
		if(temp->mName == "redBlock")
			std::cout << "!!!!" << std::endl;

	}
	*/
	
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
	for(std::vector<Ptr>::iterator itr = mChildren.begin(); itr != mChildren.end(); ++itr)
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