#include "ProjectileScriptComponent.h"
#include "GameObject.h"
#include "C_Application.h"
ProjectileScriptComponent::ProjectileScriptComponent(GameObject& gameObject)
	: ScriptComponent(gameObject)
	, mSpeed(4,4)
{
	
}


void ProjectileScriptComponent::update() 
{
	Vector2D pos = mGameObject.getPosition();
	float angle = mGameObject.getRotation();

	pos.x += sin(angle) * mSpeed.x;
	pos.y += -cos(angle) * mSpeed.y;

	mGameObject.setPosition(pos.x, pos.y);

	if (pos.y < 0 || pos.x < 0 || pos.x > mApplication->getScreenWidth() || pos.y > mApplication->getScreenHeight())
	{
		mGameObject.Destroy();
	}
}