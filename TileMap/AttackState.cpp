#include "Foreach.hpp"
#include "AttackState.h"
//#include "Player.h"
#include "PlayerLogic.h"
#include "SlashBoxLogic.h"
#include "System.h"
#include "GameObjectManager.h"
#include <iostream>

AttackState::AttackState(GameObject* player): attackQueue()
{
	spriteX = 0;
	currentCommand = nullptr;
	slashNumber = 0;
	player->mRenderComponent->setAnimation("Slash1");
}


PlayerState* AttackState::handleInput(GameObject* player, Grid& grid, const sf::Event& event)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	
	
	
	// if the Space key was pressed last frame
	if(event.type == event.KeyPressed)
	{
		
		if(event.key.code == sf::Keyboard::Space)
		{
			if(player->mRenderComponent->isAnimDelayed() == true)
			{
				if( player->mRenderComponent->currentAnim == "Slash1")
				{
					player->mRenderComponent->setAnimation("Slash2");
				}
				else if( player->mRenderComponent->currentAnim == "Slash2")
				{
					player->mRenderComponent->setAnimation("Slash3");
				}
			}


			/*
			// check if the current command's frame is almost near end...
			if(currentCommand->currentFrame >= currentCommand->numFrames - 4)
			{
				// if so, increase slash number, resetting if necessary
				slashNumber++;
				if(slashNumber == 3)
				{
					slashNumber = 0;
				}
				// then push that slash number to the attackQueue
				attackQueue.push(player->mActionCommandBinding.at(slashNumber));
			}*/
		}
	}
	
	return this;
}

PlayerState* AttackState::update(GameObject* player, sf::Time dt, Grid& grid)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	RenderComponent* render = dynamic_cast<RenderComponent*>(player->mRenderComponent);
	static bool isAttack = false;
	if(render->currentAnim == "Slash1" && render->mSpriteSet[render->currentAnim]->currentFrame == 2 && isAttack == false)
	{
		GameObjectDesc colDesc("AttackBox",sf::RectangleShape(sf::Vector2f(100,130)),
			Layer::Default,ComponentType::RenderComponent);//, std::unique_ptr<SlashBoxLogic>(new SlashBoxLogic(player)).release());
		
		GameObject* col = std::unique_ptr<GameObject>(new GameObject(colDesc)).release();
		col->mRenderComponent->mSprite.setOrigin(col->mRenderComponent->mSprite.getSize().x/2, col->mRenderComponent->mSprite.getSize().y/2);//col->getPosition().x,col->getPosition().y);
		col->mRenderComponent->mSprite.setFillColor(sf::Color::Transparent);
		col->addComponent(ComponentType::LogicComponent, std::unique_ptr<SlashBoxLogic>(new SlashBoxLogic(col)).release());
		col->addComponent(ComponentType::BoxColliderComponent, std::unique_ptr<Component>(new BoxColliderComponent(col)).release());	
		SlashBoxLogic* slashLogic = dynamic_cast<SlashBoxLogic*>(col->mLogicComponent);
		slashLogic->direction = logic->getDirection();
		slashLogic->init();
		GameObjectManager::addToLayer(col, Layer::Default);
		
		
		isAttack = true;

	}


	
		//	render->mSpriteSet["Slash1"]->m

	if( player->mRenderComponent->runSpriteAnim(*player) == SpriteAnim::SUCCESS )
	{
		// ...return to Standing state
		PlayerState* newState = std::unique_ptr<PlayerState>(new StandingState(player)).release();
		newState->entry(player);
		return newState;
	}


	/*
	// if a new attack was pushed to queue...
	if(attackQueue.empty() != true)
	{
		// ...call that command's exit and make the pending attack the current command, removing oldest attack in queue...
		currentCommand->exit();
		currentCommand = attackQueue.front();
		attackQueue.pop();
		return this;
	}
	// if currentCommand is done...
	if(currentCommand != nullptr && currentCommand->run(player) == Status::SUCCESS)
	{
		// ...return to Standing state
		PlayerState* newState = std::unique_ptr<PlayerState>(new StandingState()).release();
		newState->entry(player);
		return newState;*/
	

	return this;
}

void AttackState::entry(GameObject* player)
{
	/*
	// copy keyQueue and create local keys vector
	std::queue<sf::Keyboard::Key> playerKeySet = player->getKeyQueue();
	std::vector<sf::Keyboard::Key> keys;

	//copy key queue to vector for easy reading
	int i = 0;
	int setSize = playerKeySet.size();
	for(i = 0; i < setSize; i++)
	{
		keys.push_back(playerKeySet.front());
		playerKeySet.pop();
	}
	// clear the player key queue
	player->clearKeyQueue();
	
	// this is where a check will be done on the vector to match the input to a command chart
	int call = -1;
	FOREACH(auto p,player->mKeyActionBinding)
	{
		if(p.first == keys)
			call = p.second;
	}

	if(call != -1)
	{
		FOREACH(auto p, player->mActionCommandBinding)
		{
			if(p.first == call)
				currentCommand = p.second;
		}
	}
	else
	{
		currentCommand = player->mActionCommandBinding.at(0);
	}
	
	for(i = 0; i < keys.size(); i++)
	{
		std::cout << keys[i] << ",";
	}*/

	//std::cout << "end of attackstate->entry() " << std::endl;


}