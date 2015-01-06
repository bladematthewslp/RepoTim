#include "PlayerInput.h"
#include "GameObject.h"
#include "PlayerLogic.h"
#include "PlayerState.h"
//#include "PlayerObject.h"
#include "StandingState.h"
#include "Grid.h"
#include <iostream>


bool validKey(sf::Keyboard::Key key)
{
	switch(key)
	{
	case sf::Keyboard::Right:
	case sf::Keyboard::Left:
	case sf::Keyboard::Up:
	case sf::Keyboard::Down:
		PostQuitMessage(0);
		return true;
	}

	return false;
}
PlayerInput::PlayerInput(GameObject* gameObject) : InputComponent(gameObject)
{
	playerObject = mGameObject;
	//if(playerObject == nullptr)
	{
	//	std::cout << "dynamic cast" << std::endl;
	}
}

void PlayerInput::handleRealtimeInput(Grid& grid, const sf::Event& event)
{
	
	PlayerState* state = playerObject->mState->handleInput(playerObject,grid, event);
	if(state != mGameObject->mState)
	{
		mGameObject->mState = state;
	}
}

void PlayerInput::update(const sf::Event& event)
{
	
	
	
}


void PlayerInput::handleEvents(Grid& grid, const sf::Event& event)
{
	PlayerState* state = playerObject->mState->handleInput(playerObject,grid, event);
	if(state != mGameObject->mState)
	{
		mGameObject->mState = state;
	}
	/*if(event.type == event.KeyPressed)
	{
		sf::Keyboard::Key key = event.key.code;
		if(validKey(key) == true)
		{

			mGameObject->move(-20.0f, 0);
			mGameObject->updateTransforms();
		}

	}*/
}



