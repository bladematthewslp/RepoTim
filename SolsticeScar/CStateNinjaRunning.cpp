#include "CStateNinjaRunning.h"
#include "CStateNinjaStanding.h"
#include "CStateNinjaAttacking.h"
#include "CStateNinjaFalling.h"
#include "NinjaLogic.h"

CStateNinjaRunning::CStateNinjaRunning(GameObject* gameObject)
	: CState("CStateNinjaRunning")
{

	gameObject->mRenderComponent->setAnimation("Running");

}


CState* CStateNinjaRunning::handleInput(GameObject* character, const sf::Event& event)
{
	
	
	return this;
}
CState* CStateNinjaRunning::update(GameObject* character, sf::Time dt, Grid& grid)
{
	NinjaLogic* logic = dynamic_cast<NinjaLogic*>(character->mLogicComponent);

	character->getRenderComponent()->runSpriteAnim(*character);
	logic->setVelocityX(logic->getDirection() * logic->getRunningSpeed());
	logic->move(logic->getVelocity());

	float dist = std::abs( logic->player->getPosition().x - character->getPosition().x);

	//std::cout << dist << std::endl;

	switch(logic->getDirection())
	{
		case Direction::Right:
		{
			if(grid.checkCollisionRight(character->mBoxColliderComponent) == true)
			{
				logic->move(-logic->getVelocity().x, 0);
			}
			break;
		}
		case Direction::Left:
		{
			if(grid.checkCollisionLeft(character->mBoxColliderComponent) == true)
			{
				logic->move(-logic->getVelocity().x, 0);
			}
			break;
		}
	}

	if(grid.checkCollisionBelow(character->mBoxColliderComponent) == false   )
	{
		logic->move(sf::Vector2f(0, -grid.playerPosition.y));
		CState* newState = std::unique_ptr<CState>(new CStateNinjaFalling(character)).release();
		newState->entry(character);
		return newState;
	}

	if(dist < 125)
	{
		CState* newState = std::unique_ptr<CState>(new CStateNinjaAttacking(character)).release();
		newState->entry(character);
		return newState;
	}
	else if(dist > 400)
	{
		CState* newState = std::unique_ptr<CState>(new CStateNinjaStanding(character)).release();
		newState->entry(character);
		return newState;

	}




	return this;

}

void	CStateNinjaRunning::entry(GameObject* character)
{
	NinjaLogic* logic = dynamic_cast<NinjaLogic*>(character->mLogicComponent);
	logic->setVelocityX(logic->getDirection() * logic->getRunningSpeed());


}

void	CStateNinjaRunning::exit(GameObject* character)
{
	NinjaLogic* logic = dynamic_cast<NinjaLogic*>(character->mLogicComponent);
	logic->setVelocityX(0);


}

void CStateNinjaRunning::setKeyDownParams(GameObject* player, sf::Keyboard::Key key)
{
	NinjaLogic* logic = dynamic_cast<NinjaLogic*>(player->mLogicComponent);
	keyDown = key;
	switch(keyDown)
	{
		case sf::Keyboard::Right:
			logic->setVelocityX(logic->getRunningSpeed());
			break;
		case sf::Keyboard::Left:
			logic->setVelocityX(-logic->getRunningSpeed());
			break;
	}
}