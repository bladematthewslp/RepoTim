#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"

class InputComponent :	public Component
{
	
public:
	//GameObject* mParent;
	InputComponent(GameObject* parent);
	
	void	Awake();
	void	Destroy();
	void	FixedUpdate();
	void	LateUpdate();
	void	Start();
	void	update();
	virtual void	update(const sf::Event& event);

	virtual void handleEvents(const sf::Event& event);
	virtual void handleRealtimeInput(const sf::Event& event);
	
	~InputComponent(void);
};

