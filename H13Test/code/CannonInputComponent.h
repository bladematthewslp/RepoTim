#pragma once

#include "InputComponent.h"

class CannonInputComponent : public InputComponent
{
	float	maxShootDelay;
	float	shootDelayTimer;
	bool	shootButtonDown;
public:
	CannonInputComponent(GameObject& gameObject);

	void update(T_PressedKey pressedKeys) override;
};