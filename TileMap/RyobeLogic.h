#pragma once

#include "LogicComponent.h"
#include "RyobeRender.h"
#include "Helper.h"

class RyobeLogic : public LogicComponent
{
	GameObject*					player;
	int							mDirection;
	int							mHealth;
	bool						mIsHit;
	int							mHitCounter;
	std::map<DamageType, int>	mDamageTable;
public:
	RyobeLogic(GameObject* gameObject);


	void	update(Grid& grid);
	
	void	hit();
	int		getHealth();

	int getDirection();
	void updateDirection();

};