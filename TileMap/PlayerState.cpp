#include "PlayerState.h"
#include "PlayerLogic.h"
#include "GameObject.h"

PlayerState*  PlayerState::handleInput(GameObject* player, Grid& grid, const sf::Event& event)
{
	return this;
}

PlayerState* PlayerState::update(GameObject* player, sf::Time dt, Grid& grid)
{
	return this;
}

void PlayerState::entry(GameObject* player)
{

}

