#include "InputComponent.h"
#include "GameObject.h"
#include <iostream>

InputComponent::InputComponent(GameObject* gameObject) : Component(gameObject)
{
	
}


void InputComponent::handleEvents(const sf::Event& event)
{
}


void InputComponent::handleRealtimeInput()
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
