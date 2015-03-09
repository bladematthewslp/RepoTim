#include "InputComponent.h"
#include "GameObject.h"
#include "System.h"
#include <iostream>

InputComponent::InputComponent(GameObject* gameObject) : Component(gameObject)
{
	System::addComponent(this);
}


void InputComponent::handleEvents(const sf::Event& event)
{
}


void InputComponent::handleRealtimeInput(const sf::Event& event)
{
	
}
void InputComponent::Awake()
{
}
void InputComponent::Destroy()
{
}
void InputComponent::FixedUpdate()
{
}

void InputComponent::LateUpdate()
{
}
void InputComponent::Start()
{
	
}

void InputComponent::update()
{
}

void InputComponent::update(const sf::Event& event)
{
	
}
InputComponent::~InputComponent(void)
{
	std::vector<InputComponent*>::iterator input_itr;
	input_itr = std::remove(System::mInputComponents.begin(), System::mInputComponents.end(), this);
	System::mInputComponents.erase(input_itr, System::mInputComponents.end());
}
