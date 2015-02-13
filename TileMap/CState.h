#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "PlayerRender.h"
//#include "NinjaLogic.h"
#include "RenderComponent.h"
#include "AttackType.h"
#include "System.h"
#include "NinjaRender.h"
#include "ItemGameObject.h"
#include <vector>
#include <string>

//class Player;
struct Grid;
class Component;
class PlayerLogic;

class GameObject;
class CState // stands for 'Character' State
{
		
		std::string mStateName;
	protected:
		GameObject*	player;
	public:
		CState(std::string name = "CharacterState");// : mStateName(name){player = System::findGameObjectByName("Player");};
		virtual void		entry(GameObject* character);
		virtual void		exit(GameObject* character);
		virtual CState*		handleInput(GameObject* character, const sf::Event& event);
		virtual CState*		update(GameObject* character, sf::Time dt, Grid& grid);

		std::string getName();

};
