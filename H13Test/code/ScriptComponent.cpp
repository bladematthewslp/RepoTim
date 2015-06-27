#include "ScriptComponent.h"
#include "C_Application.h"
ScriptComponent::ScriptComponent(GameObject& gameObject)
	: Component(gameObject)
{

	mApplication->addComponent<ScriptComponent>(this);
}

ScriptComponent::~ScriptComponent()
{

}

void ScriptComponent::update()
{

}