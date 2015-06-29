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




class ClockHand : public GameObject
{
public:
	ClockHand(std::string name = "ClockHand");
};




