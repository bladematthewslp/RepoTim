#pragma once
#include <SFML/Graphics.hpp>
#include "BoxColliderComponent.h"

class NinjaBoxCollider : public BoxColliderComponent
{

public:
	NinjaBoxCollider(GameObject* gameObject);
	void	onCollisionEnter(Grid& grid, BoxColliderComponent* other);
	void	onCollisionStay(Grid& grid, BoxColliderComponent* other);
};