#include "NinjaSlashBoxLogic.h"

NinjaSlashBoxLogic::NinjaSlashBoxLogic(GameObject* gameObject)
	: LogicComponent(gameObject)
	, timer(0)
{

}

void NinjaSlashBoxLogic::init(GameObject& character, int dir, Attacks::Name attack, int timeToLast )
{
	mSpawningCharacter = &character;
	maxTime = timeToLast;
	mAttackName = attack;
	sf::Vector2f position;
	if(attack == Attacks::NINJA_SLASH_GROUND)
	{
		if(dir == 1)
		{
			position = character.getPosition() + sf::Vector2f(30, -22);
		}
		else
		{
			position = character.getPosition() + sf::Vector2f(-100, -22);
		}
	}

	mGameObject->setPosition(position);


}

void NinjaSlashBoxLogic::update(Grid& grid)
{
	timer++;
	if(timer == maxTime)
	{
		System::removeGameObject(mGameObject);	
	}

}

Attacks::Name NinjaSlashBoxLogic::getAttackName()
{
	return mAttackName;
}