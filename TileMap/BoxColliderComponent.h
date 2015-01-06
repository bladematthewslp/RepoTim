#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"


class BoxColliderComponent : public Component
{
	sf::RectangleShape mCollisionBox;
	GameObject* player;
	bool mIsVisible;
public:
	BoxColliderComponent(GameObject* gameObject);
	void update();
	void render(sf::RenderWindow& window);

	void setSize(float x, float y);

};