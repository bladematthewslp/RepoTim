#pragma once

#include <SFML/Graphics.hpp>

#include "CState.h"
class PlayerLogic;

class RunningState : public CState
{
public:
					RunningState(GameObject* player);
	void			entry(GameObject* player);
	void			exit(GameObject* character);
	CState*			handleInput(GameObject* player, const sf::Event& event);
	CState*			update(GameObject* player, sf::Time dt, Grid& grid);
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