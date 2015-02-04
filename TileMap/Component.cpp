#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject* gameObject)
{
	this->mName = "Component";
	this->mIsEnabled = true;
	this->mGameObject = gameObject;
	this->Awake();
	HRESULT l_result = CoCreateGuid(&mID);


}

Component::Component(std::string lname)
{
	this->mName = lname;
	this->mIsEnabled = true;
	this->mGameObject = nullptr;
	this->Awake();
	HRESULT l_result = CoCreateGuid(&mID);

}


void Component::Awake()
{
}
void Component::Destroy()
{
}
void Component::FixedUpdate()
{
}

void Component::LateUpdate()
{
}
void Component::Start()
{
}

void Component::Update()
{
}
