#pragma once

#include "ColliderComponent.h"
#include <array>

class ClockColliderComponent :	public ColliderComponent
{
	static std::array<Vector2D, 4> screenBounds;
public:
	ClockColliderComponent(GameObject& gameObject);
	~ClockColliderComponent();
	void update();
	virtual ColliderComponent* checkForCollision();

};

