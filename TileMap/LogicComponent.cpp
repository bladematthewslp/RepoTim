#include "LogicComponent.h"
#include <iostream>
#include "System.h"
LogicComponent::LogicComponent(GameObject* gameObject)  : Component(gameObject)
{
	System::addComponent(this);
}
void LogicComponent::Awake()
{
}
void LogicComponent::Destroy()
{
}
void LogicComponent::FixedUpdate()
{
}

void LogicComponent::LateUpdate()
{
}
void LogicComponent::Start()
{
	
}

void LogicComponent::update(Grid& grid)
{
	
}