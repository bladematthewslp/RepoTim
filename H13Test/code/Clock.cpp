#include "Clock.h"
#include "ClockRenderComponent.h"
#include "ClockScriptComponent.h"
#include "ClockColliderComponent.h"

int Clock::NUM_CLOCKS = 0;

Clock::Clock(std::string name)
	: GameObject(name)
{
	mRenderComponent = new ClockRenderComponent(*this);
	mScriptComponent = new ClockScriptComponent(*this);
	mColliderComponent = new ClockColliderComponent(*this);
	NUM_CLOCKS++;
};

Clock::~Clock()
{
	--NUM_CLOCKS;
}

ClockHand::ClockHand(std::string name)
	: GameObject(name)
{
	mRenderComponent = new ClockHandRenderComponent(*this);
}







