#pragma once

#include <SFML/Graphics.hpp>
#include "RenderComponent.h"



class NinjaRender : public RenderComponent
{
public:
	NinjaRender(GameObject* mGameObject);
	void update(sf::RenderTarget& window);
};