#include "SlashBoxLogic.h"
#include "System.h"
#include <iostream>
SlashBoxLogic::SlashBoxLogic(GameObject* gameObject) : LogicComponent(gameObject), direction(0)
{
	//mGameObject->setPosition(mGameObject->mParent->getPosition());
	player = System::findGameObjectByName("Player");
	
	
}

void SlashBoxLogic::init()
{
	if(direction == 1)
		mGameObject->setPosition(player->getPosition().x + 75, player->getPosition().y - 20);//500,50);
	else
		mGameObject->setPosition(player->getPosition().x - 75, player->getPosition().y - 20);//500,50);

	std::cout << -player->getPosition().x + 25 << std::endl;
}
void SlashBoxLogic::update()
{
	static GameObject* ninjaObject = System::findGameObjectByName("Ninja");
	
	static bool ninjaGone = false;
	if(ninjaGone == false && mGameObject->mRenderComponent->mSprite.getGlobalBounds().intersects(ninjaObject->mRenderComponent->mSprite.getGlobalBounds()))
	{
		std::cout << "!!" << std::endl;
		System::removeGameObject(ninjaObject);
		ninjaGone = true;
	}
	static float timer = 0;
	timer++;
	//mGameObject->move(-1,1);
	//std::cout << "!!" << std::endl;
	if(timer == 15)
	{
		timer = 0;
		System::removeGameObject(mGameObject);
	}
}