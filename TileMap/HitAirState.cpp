#include "HitAirState.h"
#include "FallingState.h"
#include "PlayerLogic.h"
#include "BoxColliderComponent.h"
#include "Grid.h"
#include <iostream>

HitAirState::HitAirState(GameObject* player) : CState("HitAirState")
	, hitVelocity(-5.0f, -5.0f)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	player->mRenderComponent->setAnimation("HitAirPart1");
	player->mBoxColliderComponent->setSize(120, 98);

	logic->mSoundPlayer.play(SoundEffect::DojiHit);

}

CState* HitAirState::update(GameObject* player, sf::Time dt, Grid& grid)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	
	
	static int damageTimer = 0;
	hitVelocity.x += 0.1f;
	if(hitVelocity.x >= 0)
		hitVelocity.x = 0;

	hitVelocity.y += 0.1f;

	if(hitVelocity.y > 0)
	{
		hitVelocity.y = 0;
	}
	
	logic->setVelocityX(hitVelocity.x * logic->getDirection());
	logic->setVelocityY(hitVelocity.y );
	logic->move(logic->getVelocity());

	
	if(grid.checkCollisionLeft(player->mBoxColliderComponent) == true)
	{
		logic->move(-logic->getVelocity().x, 0);
	}
	if(grid.checkCollisionRight(player->mBoxColliderComponent) == true)
	{
		logic->move(-logic->getVelocity().x, 0);
	}

	if(damageTimer == 20)
	{
		player->mRenderComponent->setAnimation("HitAirPart2");
	}

	if(player->mRenderComponent->runSpriteAnim(*player) == SpriteAnim::Status::SUCCESS)
	{
		if(player->mRenderComponent->currentAnim == "HitAirPart2")
		{
			damageTimer = 0;
			//hitVelocity = 8.0f;
			player->mBoxColliderComponent->setSize(80, 98);
			CState* newState = std::unique_ptr<CState>(new FallingState(player)).release();
			newState->entry(player);
			return newState;
		}
		//pauseTimer++;
	}
	damageTimer++;
	return this;
}

