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

LogicComponent::~LogicComponent()
{
	std::vector<LogicComponent*>::iterator log_itr;
	log_itr = std::remove(System::mLogicComponents.begin(), System::mLogicComponents.end(), this);
	System::mLogicComponents.erase(log_itr, System::mLogicComponents.end());
	
}

int LogicComponent::getDirection()
{
	//std::cout << "getDirection() not overwritten" << std::endl;
	return false;
}