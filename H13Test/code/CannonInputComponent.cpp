#include "CannonInputComponent.h"
#include "GameObject.h"
#include "C_Application.h"
#include "Projectile.h"

static const float k_PI = 3.1415926536f;

CannonInputComponent::CannonInputComponent(GameObject& gameObject)
	: InputComponent(gameObject)
{
	maxShootDelay = 15;
	shootDelayTimer = maxShootDelay;
	shootButtonDown = false;
}

void CannonInputComponent::update(T_PressedKey pressedKeys) 
{
	Vector2D pos = mGameObject.getPosition();
	float angle = mGameObject.getRotation();

	float rotationSpeed = 0.05f;

	if (shootDelayTimer != maxShootDelay)
	{
		shootDelayTimer--;
		if (shootDelayTimer <= 0)
			shootDelayTimer = maxShootDelay;
	}

	if (pressedKeys & s_KeyLeft)
	{
		angle = max(-k_PI / 2, angle - rotationSpeed);
	}

	if (pressedKeys & s_KeyRight)
	{
		angle = min( k_PI/2, angle + rotationSpeed);
	}

	if (pressedKeys & s_KeyUp)
	{
		//pos.x -= -sin(angle);
		//pos.y -= cos(angle);// max(0, pos.y - 4);
	}

	if (pressedKeys & s_KeyDown)
	{
		
		//pos.y = min(mApplication->getScreenHeight(), pos.y + 4);
	}

	if (pressedKeys & s_KeySpace)
		shootButtonDown = true;
	else
		shootButtonDown = false;

	if (shootButtonDown)
	{
		if (shootDelayTimer == maxShootDelay)
		{
			GameObject* projectile = GameObject::Create<Projectile>();
			projectile->setPosition(pos);
			projectile->setRotation(angle);
			shootDelayTimer--;
		}
	}


	mGameObject.setPosition(pos.x, pos.y);
	mGameObject.setRotation(angle);
}