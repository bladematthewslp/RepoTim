#pragma once

#include <SFML/Graphics.hpp>
#include "RenderComponent.h"

class GameObject;

class PlayerRender : public RenderComponent
{
	

public:
	sf::Image mPlayerImage;
	sf::Texture mPlayerTexture;
	
	sf::Image mPlayerTransformedImage;
	sf::Texture mPlayerTransformedTexture;
	PlayerRender(GameObject* mGameObject);
	void	update(sf::RenderTarget& window);
};