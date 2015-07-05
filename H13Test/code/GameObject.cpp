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
	, mColliderComponent(nullptr)
	, mParent(nullptr)
{
	
	
}

Vector2D	GameObject::getPosition() 
{ 
	return mPosition; 
}

void		GameObject::setPosition(float x, float y, bool updateCollider)
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


	if ( updateCollider == true && mColliderComponent)
	{
		mColliderComponent->update();
	}

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

void GameObject::setPosition(Vector2D pos, bool updateCollider)
{
	setPosition(pos.x, pos.y, updateCollider);
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

	if (mColliderComponent != nullptr)
	{
		for (auto cc = mApplication->mColliderComponents.begin(); cc != mApplication->mColliderComponents.end(); ++cc)
		{
			if ((*cc) == this->mColliderComponent)
			{
				mApplication->mColliderComponents.erase(cc);
				delete mColliderComponent;
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

std::string	GameObject::getName()
{
	return mName;
}

std::vector<GameObject*>& GameObject::getChildren()
{
	return mChildren;
}

Vector2D GameObject::getScale()
{
	return mScale;
}

void GameObject::scale(Vector2D scale)
{
	
	// scale each component of vector by scalar
	if (mRenderComponent)
	{
		Vector2D tempScale = mScale + scale;

 		auto vertices = mRenderComponent->getVertices();
		for (std::vector<Vector2D>::iterator vec = vertices.begin(); vec != vertices.end(); ++vec)
		{
			//(*vec).x *= newScale.x;
			//(*vec).y *= newScale.y;
		}
		//newScale.x = 1 / newScale.x;
		//newScale.y = 1 / newScale.y;
		mRenderComponent->scaleVertices(scale);
	}

	// update this object's scalar
	//mScale *= scale;
	mScale *= scale;

	// update scale of each child game object
	//for (std::vector<GameObject*>::iterator iter = mChildren.begin(); iter != mChildren.end(); ++iter)
	//{
	//	(*iter)->setScale(newScale );
	//}


}

void GameObject::scale(float x, float y)
{
	scale(Vector2D(x, y));
}

void GameObject::move(float x, float y, bool updateCollider)
{
	setPosition(mPosition.x + x, mPosition.y + y, updateCollider);
}
void GameObject::move(Vector2D vec, bool updateCollider)
{
	move(vec.x, vec.y, updateCollider);
}