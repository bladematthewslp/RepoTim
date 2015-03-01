#include "SlashBoxLogic.h"
#include "System.h"
#include "BoxColliderComponent.h"
#include "PlayerState.h"
#include <iostream>
SlashBoxLogic::SlashBoxLogic(GameObject* gameObject) 
	: LogicComponent(gameObject), direction(0)
	, timer(0)
{
	player = System::findGameObjectByName("Player");
	
	mSpawnPos[Attacks::PLAYER_SLASH1][0] =  sf::Vector2f(player->getPosition().x + 15,  player->getPosition().y - 80);
	mSpawnPos[Attacks::PLAYER_SLASH1][1] =  sf::Vector2f(player->getPosition().x - 125, player->getPosition().y - 80);
	mSpawnPos[Attacks::PLAYER_SLASH2][0] =  sf::Vector2f(player->getPosition() + sf::Vector2f(0, -20));
	mSpawnPos[Attacks::PLAYER_SLASH2][1] =  sf::Vector2f(player->getPosition() + sf::Vector2f(-90, -20));
	mSpawnPos[Attacks::PLAYER_SLASH3][0] =  sf::Vector2f(player->getPosition() + sf::Vector2f(-135, -135));
	mSpawnPos[Attacks::PLAYER_SLASH3][1] =  sf::Vector2f(player->getPosition() + sf::Vector2f(-105, -135));
	mSpawnPos[Attacks::PLAYER_IMPACT][0] =  sf::Vector2f(player->getPosition() + sf::Vector2f(-85, -95));
	mSpawnPos[Attacks::PLAYER_IMPACT][1] =  sf::Vector2f(player->getPosition() + sf::Vector2f(-70, -95));
	mSpawnPos[Attacks::PLAYER_CHOPPERSTYLE][0] =  sf::Vector2f(player->getPosition() + sf::Vector2f(-120, -100));
	mSpawnPos[Attacks::PLAYER_CHOPPERSTYLE][1] =  sf::Vector2f(player->getPosition() + sf::Vector2f(-120, -100));
	mSpawnPos[Attacks::PLAYER_QUICKUPRISING][0] =  sf::Vector2f(player->getPosition() + sf::Vector2f(-20, -150));
	mSpawnPos[Attacks::PLAYER_QUICKUPRISING][1] =  sf::Vector2f(player->getPosition() + sf::Vector2f(-105, -150));
	mSpawnPos[Attacks::PLAYER_QUICKSTINGER][0] =  sf::Vector2f(player->getPosition() + sf::Vector2f(-0, -70));
	mSpawnPos[Attacks::PLAYER_QUICKSTINGER][1] =  sf::Vector2f(player->getPosition() + sf::Vector2f(-120, -70));
	
}

void SlashBoxLogic::init(int dir, Attacks::Name attack, int timeToLast)
{
	maxTime = timeToLast;

	sf::Vector2f position;
	if(attack == Attacks::PLAYER_SLASH1)
	{
		if(dir == 1)
		{
			position = mSpawnPos[Attacks::PLAYER_SLASH1][0];
		}
		else
		{
			position = mSpawnPos[Attacks::PLAYER_SLASH1][1];
		}
	}
	else if(attack == Attacks::PLAYER_SLASH2)
	{
		if(dir == 1)
		{
			position = mSpawnPos[Attacks::PLAYER_SLASH2][0];
		}
		else
		{
			position = mSpawnPos[Attacks::PLAYER_SLASH2][1];
		}
	}
	else if(attack == Attacks::PLAYER_SLASH3)
	{
		if(dir == 1)
		{
			position = mSpawnPos[Attacks::PLAYER_SLASH3][0];
		}
		else
		{
			position = mSpawnPos[Attacks::PLAYER_SLASH3][1];
		}
	}
	else if(attack == Attacks::PLAYER_IMPACT)
	{
		if(dir == 1)
		{
			position = mSpawnPos[Attacks::PLAYER_IMPACT][0];
		}
		else
		{
			position = mSpawnPos[Attacks::PLAYER_IMPACT][1];
		}
	}
	else if(attack == Attacks::PLAYER_CHOPPERSTYLE)
	{
		if(dir == 1)
		{
			position = mSpawnPos[Attacks::PLAYER_CHOPPERSTYLE][0];
		}
		else
		{
			position = mSpawnPos[Attacks::PLAYER_CHOPPERSTYLE][1];
		}
	}
	else if(attack == Attacks::PLAYER_QUICKSTINGER)
	{
		if(dir == 1)
		{
			position = mSpawnPos[Attacks::PLAYER_QUICKSTINGER][0];
		}
		else
		{
			position = mSpawnPos[Attacks::PLAYER_QUICKSTINGER][1];
		}
	}
	else if(attack == Attacks::PLAYER_QUICKUPRISING)
	{
		if(dir == 1)
		{
			position = mSpawnPos[Attacks::PLAYER_QUICKUPRISING][0];
		}
		else
		{
			position = mSpawnPos[Attacks::PLAYER_QUICKUPRISING][1];
		}
	}

	mGameObject->setPosition(position);
	setAttackType(attack);
	

}
void SlashBoxLogic::update(Grid& grid)
{
	
	
	timer++;

	if(timer == maxTime)// || player->mState->getName() != "AttackState" || player->mState->getName() != "AttackStateAir")
	{
		timer = 0;
		System::removeGameObject(mGameObject);
	}
}


void SlashBoxLogic::setAttackType(Attacks::Name type)
{
	mAttackType = type;
}

Attacks::Name	SlashBoxLogic::getAttack()
{
	return mAttackType;


}

GameObject* SlashBoxLogic::getPlayer()
{
	return player;
}