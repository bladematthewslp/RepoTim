#pragma once


#include "LogicComponent.h"


class ItemLogic : public LogicComponent
{
	sf::Vector2f	mVelocity;
	float			acceleration;
public:
	ItemLogic(GameObject* gameObject);
	void	update(Grid& grid);
	void				move(sf::Vector2f dir);
	void				move(float x, float y);


};