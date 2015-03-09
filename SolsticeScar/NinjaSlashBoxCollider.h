#pragma once

#include <SFML/Graphics.hpp>
#include "BoxColliderComponent.h"



class NinjaSlashBoxCollider : public BoxColliderComponent
{
public:
	
	NinjaSlashBoxCollider(GameObject* gameObject);

	void onCollisionEnter(Grid& grid, BoxColliderComponent* other);


private:



};