#include "Clock.h"
#include "ClockRenderComponent.h"
#include "ClockScriptComponent.h"
#include "ClockColliderComponent.h"


Clock::Clock(std::string name)
	: GameObject(name)
{
	mRenderComponent = new ClockRenderComponent(*this);
	mScriptComponent = new ClockScriptComponent(*this);
	mColliderComponent = new ClockColliderComponent(*this);
};

ClockHand::ClockHand(std::string name)
	: GameObject(name)
{
	mRenderComponent = new ClockHandRenderComponent(*this);
}







