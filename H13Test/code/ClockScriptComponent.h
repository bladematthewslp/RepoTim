#pragma once
#include "ScriptComponent.h"
#include "Vector.h"
class ClockScriptComponent :public ScriptComponent
{
	GameObject* hourHand;
	GameObject* minuteHand;
	GameObject* secondHand;

	Vector2D mVelocity;
public:
	ClockScriptComponent(GameObject& gameObject);
	virtual ~ClockScriptComponent();

	virtual void update();

	Vector2D	getVelocity();
	void		setVelocity(Vector2D vel);
};

