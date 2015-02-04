#pragma once

#include "CState.h"

class CStateNinjaRunning : public CState
{
	sf::Keyboard::Key	keyDown;
public:
	CStateNinjaRunning(GameObject* gameObject);
	
	void		entry(GameObject* character);	
	void		exit(GameObject* character);
	CState*		handleInput(GameObject* character, const sf::Event& event);
	CState*		update(GameObject* character, sf::Time dt, Grid& grid);
	void		setKeyDownParams(GameObject* player, sf::Keyboard::Key key);
};