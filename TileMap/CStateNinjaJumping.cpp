#include "CStateNinjaJumping.h"
#include "CStateNinjaStanding.h"
#include "NinjaBoxCollider.h"
#include "NinjaLogic.h"

CStateNinjaJumping::CStateNinjaJumping(GameObject* character)
	: CState("CStateNinjaJumping")
{
	
}

void CStateNinjaJumping::entry(GameObject* character)
{			
	
	NinjaLogic* logic = dynamic_cast<NinjaLogic*>(character->mLogicComponent);
	logic->setVelocityY(-8);		
}			
CState*		CStateNinjaJumping::handleInput(GameObject* character, const sf::Event& event)
{
	return this;
}
CState*		CStateNinjaJumping::update(GameObject* character, sf::Time dt, Grid& grid)
{
	NinjaLogic* logic = dynamic_cast<NinjaLogic*>(character->mLogicComponent);

	sf::Vector2f velocity = logic->getVelocity();
	velocity.y += 0.2f;

	logic->setVelocity(velocity);

	logic->move(logic->getVelocity());
	if(velocity.y < 0)
	{

	}
	else if(velocity.y > 0 && grid.checkCollisionBelow(character->mBoxColliderComponent) == true   )
	{
		logic->move(sf::Vector2f(0, -grid.playerPosition.y));

		CState* newState = std::unique_ptr<CState>(new CStateNinjaStanding(character)).release();
		newState->entry(character);
		return newState;
	}
	return this;
}