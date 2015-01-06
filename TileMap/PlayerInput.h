#pragma once
#include <SFML/Graphics.hpp>
#include "InputComponent.h"
#include <queue>

class GameObject;
struct Grid;
class PlayerInput : public InputComponent
{

	std::queue<sf::Keyboard::Key>	keyQueue;
	GameObject* playerObject;
public:
	PlayerInput(GameObject* gameObject);
	void	update(const sf::Event& event);
	void handleEvents(Grid& grid, const sf::Event& event);
	void handleRealtimeInput(Grid& grid, const sf::Event& event);
};