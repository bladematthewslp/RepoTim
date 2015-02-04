#include "CStateNinjaDeadAir.h"
#include "NinjaLogic.h"
#include "PlayerLogic.h"
#include <stdlib.h>
#include <time.h>
CStateNinjaDeadAir::CStateNinjaDeadAir(GameObject* character)
{
	NinjaLogic* logic = dynamic_cast<NinjaLogic*>(character->mLogicComponent);

	done = false;
	maxFallingSpeed = 4;
	character->getRenderComponent()->setAnimation("DeadAirPart1");


	int playerHealth = dynamic_cast<PlayerLogic*>(logic->player->mLogicComponent)->getHealth();
	// randomly drop an item
	srand( time(NULL));
	int randomNumber = rand() % 200;
	if( randomNumber >= 180 &&  playerHealth < 50 )
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

void		CStateNinjaDeadAir::entry(GameObject* character, AttackType attackType)
{

}

CState*		CStateNinjaDeadAir::handleInput(GameObject* character, const sf::Event& event)
{

	return this;

}


CState*		CStateNinjaDeadAir::update(GameObject* character, sf::Time dt, Grid& grid)
{
	NinjaLogic* logic = dynamic_cast<NinjaLogic*>(character->mLogicComponent);

	if(done == false)
	{
		sf::Vector2f velocity = logic->getVelocity();
		velocity.y += 0.3f;
	
		if(velocity.y > maxFallingSpeed)
		{
			velocity.y = maxFallingSpeed;
		}
		logic->setVelocity(velocity);

		logic->move(logic->getVelocity());
	}


	if(character->getRenderComponent()->runSpriteAnim(*character) == SpriteAnim::Status::SUCCESS)
	{
		

	}
	if(done == false && grid.checkCollisionBelow(character->mBoxColliderComponent) == true   )
	{
		logic->move(sf::Vector2f(0, -grid.playerPosition.y));
		character->getRenderComponent()->setAnimation("DeadAirPart2");
		character->mBoxColliderComponent->setSize(0,0);
		done = true;
		logic->setVelocity(0,0);
	}

	return this;
}