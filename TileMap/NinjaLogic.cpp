#include "NinjaLogic.h"
#include "System.h"
#include <cmath>
#include <iostream>

NinjaLogic::NinjaLogic(GameObject* gameObject) 
	: LogicComponent(gameObject)
{
	player = System::findGameObjectByName("Player");
	if(player == nullptr)
		std::cout << "player not found" << std::endl;
	float dist = sqrt(pow((player->getPosition().x - mGameObject->getPosition().x),2) + pow((player->getPosition().y - mGameObject->getPosition().y),2));
	std::cout << dist << std::endl;
}

void NinjaLogic::update()
{
	float dist = (mGameObject->getPosition().x - player->getPosition().x);//  + mGameObject->getPosition().y * player->getPosition().y);
//	std::cout << dist << std::endl;
	mGameObject->mRenderComponent->runSpriteAnim(*mGameObject);
}