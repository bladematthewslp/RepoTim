#include "RyobeGameObject.h"



RyobeGameObject::RyobeGameObject(GameObjectDesc desc)
	: GameObject(desc)
{
	mRenderComponent = std::unique_ptr<RenderComponent>(new RyobeRender(this)).release();
	mLogicComponent  = std::unique_ptr<LogicComponent>(new RyobeLogic(this)).release();


}