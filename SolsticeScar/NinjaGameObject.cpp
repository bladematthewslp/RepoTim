#include "NinjaGameObject.h"
#include "NinjaBoxCollider.h"
#include "NinjaRender.h"
#include "NinjaLogic.h"
#include "NinjaInput.h"


NinjaGameObject::NinjaGameObject(GameObjectDesc desc)
	: GameObject(desc)
{
	mRenderComponent = std::unique_ptr<RenderComponent>(new NinjaRender(this)).release();
	mLogicComponent = std::unique_ptr<LogicComponent>(new NinjaLogic(this)).release();
	mBoxColliderComponent = std::unique_ptr<BoxColliderComponent>(new NinjaBoxCollider(this)).release();
	mInputComponent = std::unique_ptr<InputComponent>(new NinjaInput(this)).release();


}