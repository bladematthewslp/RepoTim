#include "CState.h"



CState::CState(std::string name) 
	: mStateName(name)
{
	player = System::findGameObjectByName("Player");
}

void CState::entry(GameObject* character)
{			
			
}			
CState*		CState::handleInput(GameObject* character, const sf::Event& event)
{
	return this;
}
CState*		CState::update(GameObject* character, sf::Time dt, Grid& grid)
{
	return this;
}

std::string CState::getName()
{
	return this->mStateName;
}

void CState::exit(GameObject* character)
{


}