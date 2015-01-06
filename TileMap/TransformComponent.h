#pragma once

#include <SFML\Graphics.hpp>
#include "Component.h"


class TransformComponent : public Component, public sf::Transformable
{
public:
			TransformComponent();
	void	Awake();
	void	Destroy();
	void	FixedUpdate();
	void	LateUpdate();
	void	Start();
	void	Update();

	

};