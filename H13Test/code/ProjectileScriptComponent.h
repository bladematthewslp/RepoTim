#pragma once

#include "ScriptComponent.h"
#include "Vector2D.h"
class ProjectileScriptComponent : public ScriptComponent
{
	
	
public:
	Vector2D mSpeed;
	ProjectileScriptComponent(GameObject& gameObject);
	virtual void update() override;
};