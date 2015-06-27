#include "InputComponent.h"
#include "C_Application.h"

InputComponent::InputComponent(GameObject& gameObject)
	:Component(gameObject)
{
	mApplication->addComponent<InputComponent>(this);
}

InputComponent::~InputComponent()
{

}

void InputComponent::update(T_PressedKey pressedKey)
{

}