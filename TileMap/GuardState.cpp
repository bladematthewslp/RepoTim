#include "GuardState.h"
GuardState::GuardState(GameObject* player)
{
	spriteX = 0;
	player->mRenderComponent->setAnimation("Guarding");
}

PlayerState* GuardState::handleInput(GameObject* player, Grid& grid, const sf::Event& event)
{
	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		PlayerState* newState = std::unique_ptr<PlayerState>( new StandingState(player) ).release();
		newState->entry(player);
		return newState;
	}
	return this;
}


PlayerState* GuardState::update(GameObject* player, sf::Time dt, Grid& grid)
{
	//player->getSprite().setTextureRect(sf::IntRect(spriteX * 200, 400, 200, 200));
	player->mRenderComponent->runSpriteAnim(*player);
	return this;
}

void GuardState::entry(GameObject* player)
{
	//player->getSprite().setTextureRect(sf::IntRect(spriteX * 200, 400, 200, 200));

}