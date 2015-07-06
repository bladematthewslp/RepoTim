#pragma once

#include "GameObject.h"

static const float k_PI = 3.1415926536f;

class Clock : public GameObject
{
	
public:
	static int NUM_CLOCKS;
	Clock(std::string name = "Clock");
	~Clock();
};




class ClockHand : public GameObject
{
public:
	ClockHand(std::string name = "ClockHand");
};




