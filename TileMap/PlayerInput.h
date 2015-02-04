#pragma once
#include <SFML/Graphics.hpp>
#include "InputComponent.h"
#include <queue>

class GameObject;
struct Grid;
class PlayerInput : public InputComponent
{
	int								keyDelayTimer;
	int								keyQueueTimer;
	std::queue<sf::Keyboard::Key>*	keyQueue;
	GameObject*						playerObject;
public:
	PlayerInput(GameObject* gameObject);

	bool							checkValidCommand();
	void							update(const sf::Event& event);
	void							handleEvents(const sf::Event& event);
	void							handleRealtimeInput(const sf::Event& event);
	std::queue<sf::Keyboard::Key>*	getKeyQueue();
	void							handleKeyQueue();
	void							clearKeyQueue();
};