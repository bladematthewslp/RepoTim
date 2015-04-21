#include "GuardState.h"

GuardState::GuardState(GameObject* player)
	: CState("GuardState")
{
	spriteX = 0;
	timer = 0;
	//player->mRenderComponent->setAnimation("Guarding");

}

CState* GuardState::handleInput(GameObject* player, const sf::Event& event)
{
	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		CState* newState = std::unique_ptr<CState>( new StandingState(player) ).release();
		newState->entry(player);
		return newState;
	}
	return this;
}


CState* GuardState::update(GameObject* player, sf::Time dt, Grid& grid)
{
	//player->getSprite().setTextureRect(sf::IntRect(spriteX * 200, 400, 200, 200));
	player->mRenderComponent->runSpriteAnim(*player);
	if(timer != 0)
	{
		timer--;
		if(timer == 0)
		{
			CState* newState = std::unique_ptr<CState>( new StandingState(player) ).release();
			newState->entry(player);
			return newState;
		}

	}
	return this;
}

void GuardState::entry(GameObject* player)
{
	//player->getSprite().setTextureRect(sf::IntRect(spriteX * 200, 400, 200, 200));

}

void GuardState::block(GameObject* player)
{
	//if(player->mRenderComponent->currentAnim == "Guarding")
	timer = 15;
		player->mRenderComponent->setAnimation("Blocking");
	//else
	//	player->mRenderComponent->setAnimation("Guarding");
}