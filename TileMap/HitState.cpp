#include "HitState.h"
#include "StandingState.h"
#include "PlayerLogic.h"
#include "BoxColliderComponent.h"
#include "Grid.h"
#include <iostream>

HitState::HitState(GameObject* player) : CState("HitState")
	, hitVelocity(6.0f)
{
	player->mRenderComponent->setAnimation("Hit");
	player->mBoxColliderComponent->setSize(120, 98);
}

CState* HitState::update(GameObject* player, sf::Time dt, Grid& grid)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	
	
	static int pauseTimer = 0;
	hitVelocity -= 0.1f;

	if(hitVelocity <= 0)
		hitVelocity = 0;
	
	logic->setVelocityX(hitVelocity * -logic->getDirection());
	//logic->move(logic->getVelocity());


	if(grid.checkCollisionLeft(player->mBoxColliderComponent) == true)
	{
		logic->move(-logic->getVelocity().x, 0);
	}
	if(grid.checkCollisionRight(player->mBoxColliderComponent) == true)
	{
		logic->move(-logic->getVelocity().x, 0);
	}

	if(pauseTimer == 100)
	{
		player->mRenderComponent->setAnimation("HitRecover");
	}

	if(player->mRenderComponent->runSpriteAnim(*player) == SpriteAnim::Status::SUCCESS)
	{
		if(player->mRenderComponent->currentAnim == "Hit")
		{
			pauseTimer = 0;
			hitVelocity = 8.0f;
			player->mBoxColliderComponent->setSize(80, 98);
			CState* newState = std::unique_ptr<CState>(new StandingState(player)).release();
			newState->entry(player);
			return newState;
		}
		pauseTimer++;
	}
	
	return this;
}