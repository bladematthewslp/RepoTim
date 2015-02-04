#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "CState.h"

class CState;

class PlayerObject : public GameObject
{
public:
	PlayerObject(GameObjectDesc desc);
	CState*		mState;
};