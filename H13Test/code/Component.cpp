
#include "C_Application.h"
#include "Component.h"
#include "GameObject.h"

C_Application* Component::mApplication = nullptr;

Component::Component(GameObject& gameObject)
	: mGameObject(gameObject)
	, mEnabled(true)
{
	
}

Component::~Component()
{

}

void Component::setApplication(C_Application* app)
{
	mApplication = app;
}

void Component::update()
{

}


bool Component::getEnabled()
{
	return mEnabled;
}
void		Component::setEnabled(bool flag)
{
	mEnabled = flag;
}