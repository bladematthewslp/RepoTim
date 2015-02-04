#pragma once

#include <SFML/Graphics.hpp>
#include "BoxColliderComponent.h"

class SlashBoxBoxCollider : public BoxColliderComponent
{
public:

	SlashBoxBoxCollider(GameObject* gameObject);

	void onCollisionEnter(Grid& grid, BoxColliderComponent* other);


};