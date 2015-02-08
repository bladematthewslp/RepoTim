#include "RyobeGameObject.h"



RyobeGameObject::RyobeGameObject(GameObjectDesc desc)
	: GameObject(desc)
{
	mRenderComponent = std::unique_ptr<RenderComponent>(new RyobeRender(this)).release();
	mLogicComponent  = std::unique_ptr<LogicComponent>(new RyobeLogic(this)).release();
	mBoxColliderComponent = std::unique_ptr<BoxColliderComponent>(new RyobeBoxCollider(this)).release();
	mBoxColliderComponent->setSize(45, 80);
	//mBoxColliderComponent->setVisible(true);
}