#include "RyobeLogic.h"
#include "CStateRyobeStanding.h"


RyobeLogic::RyobeLogic(GameObject* gameObject)
	: LogicComponent(gameObject)
{
	
	
	CState* state = std::unique_ptr<CState>(new CStateRyobeStanding(mGameObject)).release();
	state->entry(mGameObject);
	mGameObject->mState = state;
	
}

void RyobeLogic::update(Grid& grid)
{
	

	CState* newState = mGameObject->mState->update(mGameObject, sf::seconds(1.0/60.0f), grid);
	if(mGameObject->mState != newState)
	{
		std::cout << "!!" << std::endl;
		mGameObject->mState = newState;
	}


}