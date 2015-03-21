#pragma once


#include <SFML/Graphics.hpp>
#include <string>
#include "GameObject.h"
#include <ObjBase.h>
#include <Guiddef.h>

class GameObject;

class Component
{
	public:
	std::string		mName;
	GUID			mID;
	

	GameObject*		mGameObject;
	bool			mIsEnabled;


	Component(GameObject* gameObject = nullptr);
	Component(std::string name);

	virtual void	Awake();
	virtual void	Destroy();
	virtual void	FixedUpdate();
	virtual void	LateUpdate();
	virtual void	Start();
	virtual void	Update();


};

struct ComponentComparer
{
	std::string mName;

	ComponentComparer(std::string name)
		: mName(name)
	{


	}

	bool operator() (Component* lObject)
	{
		return (lObject->mName == mName? true : false);
	}

};