#include "KnockoutState.h"
#include "StandingState.h"
#include "PlayerLogic.h"
#include "Grid.h"


KnockoutState::KnockoutState(GameObject* player)
	: CState("KnockoutState")
	, mVelocity(-8,0)
{
	dynamic_cast<PlayerRender*>(player->mRenderComponent)->setAnimation("Knockout");
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	int dir = logic->getDirection();
	dynamic_cast<PlayerLogic*>(player->mLogicComponent)->setVelocityX(-8 * dir);
}


CState*		KnockoutState::handleInput(GameObject* player, const sf::Event& event)
{

	return this;
}

CState*		KnockoutState::update(GameObject* player, sf::Time dt, Grid& grid)
{
	PlayerRender* render = dynamic_cast<PlayerRender*>(player->mRenderComponent);
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	
	float friction = 0.2f;

	sf::Vector2f vel = logic->getVelocity();
	switch(logic->getDirection())
	{
		case Direction::Right:
			vel.x += friction;
			if(vel.x >= 0)
				vel.x = 0;
			break;
		case Direction::Left:
			vel.x -= friction;
			if(vel.x <= 0)
				vel.x = 0;
			break;
	}

	logic->setVelocityX(vel.x);
	logic->move(logic->getVelocity());

	// Check collision
	if(grid.checkCollisionLeft(player->mBoxColliderComponent) == true)
	{
		logic->move(-logic->getVelocity().x, 0);
	}
	if(grid.checkCollisionRight(player->mBoxColliderComponent) == true)
	{
		logic->move(-logic->getVelocity().x, 0);
	}


	if(render->runSpriteAnim(*player) == SpriteAnim::SUCCESS)
	{
		if(render->currentAnim == "Knockout")
		{
			if(logic->getHealth() > 0)
			{
				render->setAnimation("HitRecover");
			}
		}
		else if(render->currentAnim == "HitRecover")
		{
			CState* state = std::unique_ptr<CState>(new StandingState(player)).release();
			return state;
		}
		else
		{
			// you dead
		}
	}
	return this;
}

void		KnockoutState::entry(GameObject* player)
{

}