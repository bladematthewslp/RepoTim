#pragma once

#include <SFML\Graphics.hpp>
#include "Scene.h"
#include "World.h"
#include "Helper.h"
#include "WorldIdentifier.h"

#include <map>
#include <functional>


class SceneStack;

class GameScene : public Scene
{
	sf::RectangleShape	mShape;
	
	World::Ptr			mCurrentWorld;
	World*				mWorld;
public:
	GameScene(SceneStack& stack, Context& context);

	bool handleEvent(sf::Event& event);
	bool handleInput(sf::Event& event);

	bool update(sf::Time dt);
	void draw();

	std::map<Worlds::ID, std::function<World::Ptr()>> mWorldFactories;
	std::vector<Worlds::ID> mWorlds;


	template <typename T>
	void registerWorld(Worlds::ID);

	World::Ptr createWorld(Worlds::ID);

};

template <typename T>
void GameScene::registerWorld(Worlds::ID worldID)
{
	
	mWorldFactories[worldID] = [this] ()
	{
		return World::Ptr(new T(mStack->mContext) );
	};
	
	mWorlds.push_back(worldID);
}