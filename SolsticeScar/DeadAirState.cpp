#include "DeadAirState.h"
#include "PlayerLogic.h"

DeadAirState::DeadAirState(GameObject* player)
	: CState("DeadState")
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	dead = false;
	player->getRenderComponent()->setAnimation("KnockoutAirPart1");
	hitVelocity = sf::Vector2f(-5,-3);
	//std::cout << "Knockout" << std::endl;

	logic->mSoundPlayer.play(SoundEffect::DojiDead);

}


CState* DeadAirState::update(GameObject* player, sf::Time dt, Grid& grid)
{

	player->getRenderComponent()->runSpriteAnim(*player);
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	
	hitVelocity.x += 0.1f;
	if(hitVelocity.x >= 0)
		hitVelocity.x = 0;

	hitVelocity.y += 0.1f;

	if(dead == true)
	{
		hitVelocity.y = 0;
		//player->mRenderComponent->setAnimation("HitAirPart2");
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
	if(grid.checkCollisionBelow(player->mBoxColliderComponent) == true && dead == false  )
	{
		logic->move(sf::Vector2f(0, -grid.playerPosition.y ));
		player->mRenderComponent->setAnimation("KnockoutAirPart2");
		dead = true;
	}


	return this;
}
