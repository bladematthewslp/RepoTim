#pragma once

#include <SFML/Graphics.hpp>
#include "BoxColliderComponent.h"

class GameObject;

class PlayerBoxCollider : public BoxColliderComponent
{
	GameObject*			GUIRedOrbObject;
public:
	PlayerBoxCollider(GameObject* gameObject);

	void				onCollisionEnter(Grid& grid, BoxColliderComponent* other);
	void				onCollisionStay(Grid& grid, BoxColliderComponent* other);
	BoxColliderComponent*				onCollisionExit(Grid& grid, BoxColliderComponent* other);
};