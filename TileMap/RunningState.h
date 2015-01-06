#pragma once

#include <SFML/Graphics.hpp>

#include "PlayerState.h"
class PlayerLogic;

class RunningState : public PlayerState
{
public:
					RunningState(GameObject* player);
	void			entry(GameObject* player);
	PlayerState*	handleInput(GameObject* player, Grid& grid, const sf::Event& event);
	PlayerState*	update(GameObject* player, sf::Time dt, Grid& grid);
	void			setKeyDownParams(GameObject* player, sf::Keyboard::Key key);
private:
	sf::Keyboard::Key	keyDown;
	bool				isLeftKeyDown;
	bool				isRightKeyDown;
	bool				wasLeftPressedLastFrame;
	bool				wasRightPressedLastFrame;

	unsigned int		spriteTimer;
	int					playSpeed;
	int					numFrames;
	unsigned int		currentFrame;

};