#include "CStateNinjaHitAirToGround.h"
#include "CStateNinjaStanding.h"
#include "NinjaLogic.h"


CStateNinjaHitAirToGround::CStateNinjaHitAirToGround(GameObject* character)
	: CState("CStateNinjaHitAirToGround")
{
	NinjaLogic* logic = dynamic_cast<NinjaLogic*>(character->mLogicComponent);
	player = System::findGameObjectByName("Player");
	timerToStand = 0;
	character->mRenderComponent->setAnimation("AirHitToGround1");

	float dist = character->getPosition().x - player->getPosition().x;
	character->setPosition(player->getPosition() + sf::Vector2f(dist, 5));
	logic->mSoundPlayer.play(SoundEffect::NinjaHit);
}



CState* CStateNinjaHitAirToGround::update(GameObject* character, sf::Time dt, Grid& grid)
{
	NinjaRender* render = dynamic_cast<NinjaRender*>(character->getRenderComponent());
	NinjaLogic* logic = dynamic_cast<NinjaLogic*>(character->mLogicComponent);

	


	if(logic->isGrounded() == false)
	{
		//std::cout << "grounded is false" << std::endl;
		logic->setVelocityY(8);
		logic->move(0, logic->getVelocity().y);

		if(grid.checkCollisionBelow(character->mBoxColliderComponent) == true  )
		{
			logic->move(sf::Vector2f(0, -grid.playerPosition.y));
			character->mRenderComponent->setAnimation("AirHitToGround2");
			logic->setVelocityY(0);
			
		}
	}
	if(character->mRenderComponent->currentAnim == "AirHitToGround2")
	{
		timerToStand += dt.asSeconds();
		
		if(timerToStand >= 1)
		{
			character->mRenderComponent->setAnimation("LayToStand");
		}
	}
	if( character->mRenderComponent->runSpriteAnim(*character) == SpriteAnim::Status::SUCCESS)
	{
		if(character->mRenderComponent->currentAnim == "LayToStand")
		{
			CState* newState = std::unique_ptr<CState>(new CStateNinjaStanding(character)).release();
			newState->entry(character);
			return newState;
		}


	}
	return this;

}