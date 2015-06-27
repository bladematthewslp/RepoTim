#pragma once

#include "Component.h"

class ScriptComponent : public Component
{

	public:
		ScriptComponent(GameObject& gameObject);
		virtual ~ScriptComponent();
		virtual void update();
};