#pragma once

#include "ColliderComponent.h"

class ClockColliderComponent :	public ColliderComponent
{
	
public:
	ClockColliderComponent(GameObject& gameObject);
	~ClockColliderComponent();

	void update();

	virtual ColliderComponent* checkForCollision(ColliderComponent* other);

};

