#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "PlayerState.h"

class PlayerState;

class PlayerObject : public GameObject
{
public:
	PlayerObject(GameObjectDesc desc);
	PlayerState*		mState;
};