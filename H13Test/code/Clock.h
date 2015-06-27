#pragma once

#include "RenderComponent.h"
#include "ScriptComponent.h"
#include "GameObject.h"

static const float k_PI = 3.1415926536f;

class Clock : public GameObject
{

public:
	Clock(std::string name = "Clock");
};

class ClockRenderComponent : public RenderComponent
{
public:
	ClockRenderComponent(GameObject& gameObject);

};

class ClockScriptComponent : public ScriptComponent
{
	GameObject* hourHand;
	GameObject* minuteHand;
	GameObject* secondHand;

	Vector2D mVelocity;
public:
	
	ClockScriptComponent(GameObject& gameObject);
	~ClockScriptComponent();
	virtual void update();
};


class ClockHand : public GameObject
{
public:
	ClockHand(std::string name = "ClockHand");
};


class ClockHandRenderComponent : public RenderComponent
{

	public:
		ClockHandRenderComponent(GameObject& gameObject);
};





