#pragma once


#include <string>
#include <vector>
#include <memory>



struct  Vector2D;


#include "RenderComponent.h"
#include "InputComponent.h"
#include "ScriptComponent.h"
#include "C_Application.h"

namespace ComponentType
{
	enum type
	{
		None			= 0,
		RenderComponent = 1 << 0,
		InputComponent	= 1 << 1,
		ScriptComponent = 1 << 2,
	};
}


class GameObject
{

	private:
		void					removeAllComponentsAndGameObject();
	protected:
		std::string				mName;
		Vector2D				mPosition;
		float					mAngle;
		Vector2D				mScale;
		static C_Application*	mApplication;
		GameObject*				mParent;

		std::vector<GameObject*> mChildren;

	public:
		
		GameObject(std::string name = "GameObject");
		~GameObject();
		template <typename T>
		static GameObject* Create();
		static GameObject* Create(std::string name = "GameObject");

		void Destroy();
		static void Destroy(GameObject& gameObject);

		RenderComponent*	mRenderComponent;
		InputComponent*		mInputComponent;
		ScriptComponent*	mScriptComponent;

		Vector2D	getPosition();
		void		setPosition(float x, float y);
		void		setPosition(Vector2D pos);
		void		updateChildrenPositions(Vector2D pos);
		
		float		getRotation();
		void		setRotation(float radians);

		Vector2D	getScale();
		void		setScale(Vector2D scalar);
		void		setScale(float x, float y);

		static void	setApplicaton(C_Application* application);

		std::vector<GameObject*>& getChildren();
		void addChild(GameObject* child);
};

template <typename T>
GameObject* GameObject::Create()
{
	std::unique_ptr<GameObject> newGameObject = std::make_unique<T>();
	GameObject* obj = newGameObject.get();
	mApplication->mGameObjects.push_back(std::move(newGameObject));

	return obj;
}