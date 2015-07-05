#pragma once

#include "ScriptComponent.h"

class ProjectileScriptComponent : public ScriptComponent
{
	float speed;
	
public:
	ProjectileScriptComponent(GameObject& gameObject);
	virtual void update() override;
};