#include "GameObject.h"
#include "Cannon.h"
#include "Vector.h"
#include "C_Application.h"
#include "Clock.h"
#include <memory>

C_Application*	GameObject::mApplication;

GameObject* GameObject::Create(std::string name)
{
	std::unique_ptr<GameObject> newGameObject = std::make_unique<GameObject>(name);
	
	GameObject* obj = newGameObject.get();

	mApplication->mGameObjects.push_back(std::move(newGameObject));

	return obj;
}





GameObject::GameObject(std::string name)
	: mAngle(0)
	, mPosition()
	, mScale(1,1)
	, mName(name)
	, mRenderComponent(nullptr)
	, mInputComponent(nullptr)
	, mScriptComponent(nullptr)
	, mParent(nullptr)
{
	
	
}

Vector2D	GameObject::getPosition() 
{ 
	return mPosition; 
}

void		GameObject::setPosition(float x, float y)
{
	Vector2D worldPosition;// x, y);
	GameObject* ancestor = mParent;
	while (ancestor != nullptr)
	{
		worldPosition += ancestor->getPosition();
		ancestor = ancestor->mParent;
	}
	mPosition.x = worldPosition.x + x;
	mPosition.y = worldPosition.y + y;

	for (std::vector<GameObject*>::iterator iter = mChildren.begin(); iter != mChildren.end(); ++iter)
	{
		(*iter)->updateChildrenPositions(mPosition);
	}
}

void GameObject::updateChildrenPositions(Vector2D pos)
{
	for (std::vector<GameObject*>::iterator iter = mChildren.begin(); iter != mChildren.end(); ++iter)
	{
		(*iter)->updateChildrenPositions(pos);
	}

	mPosition.x += (pos.x - mPosition.x);
	mPosition.y += (pos.y - mPosition.y);
}

void GameObject::setPosition(Vector2D pos)
{
	setPosition(pos.x, pos.y);
}

float		GameObject::getRotation()
{
	return mAngle;
}
void		GameObject::setRotation(float radians)
{
	mAngle = radians;
}

void GameObject::addChild(GameObject* child)
{
	mChildren.push_back(child);
	child->mParent = this;

	child->setPosition(mPosition);

}

void GameObject::Destroy()
{
	std::function<void()> destroyGameObject = [this]()
	{
		this->removeAllComponentsAndGameObject();
	};

	mApplication->mCommandQueue.push(destroyGameObject);

}
void GameObject::Destroy(GameObject& gameObject)
{
	std::function<void()> destroyGameObject = [&]()
	{
		gameObject.removeAllComponentsAndGameObject();
	};

	mApplication->mCommandQueue.push(destroyGameObject);

}

GameObject::~GameObject()
{

	
}

void GameObject::setApplicaton(C_Application* application)
{
	mApplication = application;
}

void GameObject::removeAllComponentsAndGameObject()
{
	if (mRenderComponent != nullptr)
	{
		for (std::vector<RenderComponent*>::iterator rc = mApplication->mRenderComponents.begin(); rc != mApplication->mRenderComponents.end(); ++rc)
		{
			if ((*rc) == this->mRenderComponent)
			{
				mApplication->mRenderComponents.erase(rc);
				delete mRenderComponent;
				break;
			}
		}
	}

	if (mInputComponent != nullptr)
	{
		for (std::vector<InputComponent*>::iterator ic = mApplication->mInputComponents.begin(); ic != mApplication->mInputComponents.end(); ++ic)
		{
			if ((*ic) == this->mInputComponent)
			{
				mApplication->mInputComponents.erase(ic);
				delete mInputComponent;
				break;
			}
		}
	}

	
	if (mScriptComponent != nullptr)
	{
		for (auto sc = mApplication->mScriptComponents.begin(); sc != mApplication->mScriptComponents.end(); ++sc)
		{
			if ((*sc) == this->mScriptComponent)
			{
				mApplication->mScriptComponents.erase(sc);
				delete mScriptComponent;
				break;
			}
		}
	}

	

	for (std::vector<std::unique_ptr<GameObject>>::iterator gameObject = mApplication->mGameObjects.begin(); gameObject != mApplication->mGameObjects.end(); ++gameObject)
	{
		if ((*gameObject).get() == this)
		{
			mApplication->mGameObjects.erase(gameObject);
			break;
		}
	}
}

std::vector<GameObject*>& GameObject::getChildren()
{
	return mChildren;
}

Vector2D GameObject::getScale()
{
	return mScale;
}

void GameObject::setScale(Vector2D scalar)
{
	
	// scale each component of vector by scalar
	if (mRenderComponent)
	{
		auto& vertices = mRenderComponent->getVertices();
		for (std::vector<Vector2D>::iterator vec = vertices.begin(); vec != vertices.end(); ++vec)
		{
			(*vec).x *= (1 /mScale.x) * scalar.x;
			(*vec).y *= (1 /mScale.y) * scalar.y;
		}
	}

	// update this object's scalar
	mScale = scalar;

	// update scale of each child game object
	for (std::vector<GameObject*>::iterator iter = mChildren.begin(); iter != mChildren.end(); ++iter)
	{
		(*iter)->setScale(mScale);
	}


}

void GameObject::setScale(float x, float y)
{
	setScale(Vector2D(x, y));
}