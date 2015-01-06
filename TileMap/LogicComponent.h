#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"

class LogicComponent : public Component
{
public:
	//GameObject*		mParent;


	LogicComponent(GameObject* gameObject);
	void	Awake();
	void	Destroy();
	void	FixedUpdate();
	void	LateUpdate();
	void	Start();
	virtual void	update();


};