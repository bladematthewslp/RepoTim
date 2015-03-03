#include "CStateNinjaDead.h"
#include "NinjaBoxCollider.h"
#include "NinjaLogic.h"
#include "PlayerLogic.h"

#include <iostream>

CStateNinjaDead::CStateNinjaDead(GameObject* character)
	: CState("CStateNinjaDead")
{
	NinjaLogic* logic = dynamic_cast<NinjaLogic*>(character->mLogicComponent);
	character->mRenderComponent->setAnimation("HitAndDie");

	int playerHealth = dynamic_cast<PlayerLogic*>(logic->player->mLogicComponent)->getHealth();
	// remove component here (needs correct implementation)
	character->mBoxColliderComponent->setSize(0,0);
	character->mBoxColliderComponent = nullptr;
	
	srand( time(NULL));
	int randomNumber = rand() % 200;
	if( randomNumber >= 186 &&  playerHealth < 50 )
	{
		GameObjectDesc itemDesc("GreenOrb", sf::RectangleShape(sf::Vector2f(27,45)),Layer::Default, ComponentType::RenderComponent);
		ItemGameObject* item = std::unique_ptr<ItemGameObject>(new ItemGameObject(itemDesc)).release();
		item->setItemType(Item::GreenOrb);
		item->setPosition(character->getPosition() + sf::Vector2f(-10,-15));
	}
	if( randomNumber >= 190 &&  playerHealth > 50)
	{
		GameObjectDesc itemDesc("GreenOrb", sf::RectangleShape(sf::Vector2f(27,45)),Layer::Default, ComponentType::RenderComponent);
		ItemGameObject* item = std::unique_ptr<ItemGameObject>(new ItemGameObject(itemDesc)).release();
		item->setItemType(Item::GreenOrb);
		item->setPosition(character->getPosition() + sf::Vector2f(-10,-15));
	}
	else if(randomNumber > 1 && randomNumber < 180)
	{
		GameObjectDesc itemDesc("RedOrb", sf::RectangleShape(sf::Vector2f(27,45)),Layer::Default, ComponentType::RenderComponent);
		ItemGameObject* item = std::unique_ptr<ItemGameObject>(new ItemGameObject(itemDesc)).release();
		item->setItemType(Item::RedOrb);
		item->setPosition(character->getPosition() + sf::Vector2f(-10,-15));

	}

	
}



CState* CStateNinjaDead::update(GameObject* character, sf::Time dt, Grid& grid)
{
	NinjaRender* render = dynamic_cast<NinjaRender*>(character->getRenderComponent());
	render->runSpriteAnim(*character) ;

	//std::cout << " CSTATENINJADEAD" << std::endl;
	return this;
}