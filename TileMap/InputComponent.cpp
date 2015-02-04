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
}
