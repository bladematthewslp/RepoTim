#pragma once

#include "BoxColliderComponent.h"


class RyobeBoxCollider : public BoxColliderComponent
{

public:
	RyobeBoxCollider(GameObject* character);

	void	onCollisionEnter(Grid& grid, BoxColliderComponent* other);


};