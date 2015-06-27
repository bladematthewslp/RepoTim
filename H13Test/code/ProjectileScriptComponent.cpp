#include "ProjectileScriptComponent.h"
#include "GameObject.h"
#include "C_Application.h"
ProjectileScriptComponent::ProjectileScriptComponent(GameObject& gameObject)
	: ScriptComponent(gameObject)
{
	speed = 4;
}

void ProjectileScriptComponent::update() 
{
	Vector2D pos = mGameObject.getPosition();
	float angle = mGameObject.getRotation();

	pos.x += sin(angle) * speed;
	pos.y += -cos(angle) * speed;// speed;

	

	mGameObject.setPosition(pos.x, pos.y);

	if (pos.y < 0 || pos.x < 0 || pos.x > mApplication->getScreenWidth() )
		mGameObject.Destroy();
}