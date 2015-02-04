#pragma once


#include "GameObject.h"

namespace Item
{
	enum Type
	{
		RedOrb,
		GreenOrb
	};

}

class ItemGameObject : public GameObject
{
public:
	ItemGameObject(GameObjectDesc desc);
	void setItemType(Item::Type item);

};