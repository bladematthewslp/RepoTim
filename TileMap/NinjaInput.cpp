#include "NinjaInput.h"
#include "GameObject.h"
#include "PlayerLogic.h"
#include "CState.h"
//#include "PlayerObject.h"
#include "StandingState.h"
#include "Grid.h"
#include <iostream>




NinjaInput::NinjaInput(GameObject* gameObject) : InputComponent(gameObject)
{
	//playerObject = mGameObject;
	//if(playerObject == nullptr)
	{
	//	std::cout << "dynamic cast" << std::endl;
	}
}

void NinjaInput::handleRealtimeInput(const sf::Event& event)
{
	
	CState* state = mGameObject->mState->handleInput(mGameObject, event);
	if(state != mGameObject->mState)
	{
		mGameObject->mState = state;
	}
}

void NinjaInput::update(const sf::Event& event)
{
	
	
	
}


void NinjaInput::handleEvents(const sf::Event& event)
{
	CState* state = mGameObject->mState->handleInput(mGameObject, event);
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



