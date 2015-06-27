#include "Cannon.h"
#include "CannonRenderComponent.h"
#include "CannonInputComponent.h"

Cannon::Cannon()
	: GameObject()
{
	mName = "Cannon";
	mRenderComponent = new CannonRenderComponent(*this);
	mInputComponent = new CannonInputComponent(*this);
}

/*
Cannon::Cannon(std::string name)
	: GameObject(name)
{
	mName = "Cannon";
	mRenderComponent = new CannonRenderComponent(*this);
	mInputComponent = new CannonInputComponent(*this);
}

*/