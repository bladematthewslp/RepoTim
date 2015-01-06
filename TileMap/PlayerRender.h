#pragma once

#include <SFML/Graphics.hpp>
#include "RenderComponent.h"



class PlayerRender : public RenderComponent
{
	sf::Image mPlayerImage;
	sf::Texture mPlayerTexture;
	

public:

	PlayerRender(GameObject* mGameObject);
	void	update();
};