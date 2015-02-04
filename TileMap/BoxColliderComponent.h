#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"
#include "System.h"
#include "Grid.h"
#include <vector>
#include <array>
#include <set>
struct Grid;

class BoxColliderComponent : public Component
{
protected:
			// set of objects the collider is colliding with
	sf::RectangleShape				mCollisionBox;
	GameObject*						player;
	bool							mIsVisible;
	std::vector<std::array<int, 2>> mOccupiedCells;
	
public:
	std::set<BoxColliderComponent*>	mAddedColliders;	
	std::set<BoxColliderComponent*>	mColliders;	
	std::set<BoxColliderComponent*>	mRemovedColliders;	

	BoxColliderComponent(GameObject* gameObject);
	void update();
	void render(sf::RenderWindow& window);
	
	bool							mDeleted;
	sf::RectangleShape*				getCollisionBox();
	void							setSize(float x, float y);
	void							setVisible(bool isVisible);
	void							setOrigin(sf::Vector2f origin);
	virtual void					onCollisionEnter(Grid& grid, BoxColliderComponent* other);
	virtual void					onCollisionStay(Grid& grid, BoxColliderComponent* other);
	virtual BoxColliderComponent*					onCollisionExit(Grid& grid, BoxColliderComponent* other);
	std::vector<std::array<int, 2>> getOccupiedCells();

};