#pragma once
#include <SFML/Graphics.hpp>
#include "InputComponent.h"
#include <queue>

class GameObject;
struct Grid;
class NinjaInput : public InputComponent
{

	std::queue<sf::Keyboard::Key>	keyQueue;
	//GameObject* playerObject;
public:
	NinjaInput(GameObject* gameObject);
	void	update(const sf::Event& event);
	void handleEvents(const sf::Event& event);
	void handleRealtimeInput(const sf::Event& event);
};