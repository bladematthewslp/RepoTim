#include "AttackBlockedAirState.h"
#include "FallingState.h"
#include "PlayerLogic.h"

AttackBlockedAirState::AttackBlockedAirState(GameObject* character)
	: CState("AttackBlockedAirState")
	, hitVelocity(-5.0f, -5.0f)
{
	player->mRenderComponent->setAnimation("HitAirPart2");
}

CState* AttackBlockedAirState::update(GameObject* character, sf::Time dt, Grid& grid)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
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

	if(player->mRenderComponent->runSpriteAnim(*player) == SpriteAnim::Status::SUCCESS)
	{

		CState* newState = std::unique_ptr<CState>(new FallingState(player)).release();
		newState->entry(player);
		return newState;
	}


	return this;
}