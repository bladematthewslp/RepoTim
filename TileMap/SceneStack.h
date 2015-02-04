#pragma once

#include <SFML/Graphics.hpp>

#include "Scene.h"
#include <vector>
#include <map>
#include <functional>

class SceneStack
{
public:
	enum Action
	{
		Push,
		Pop,
		Clear
	};
				
	explicit	SceneStack(Scene::Context context);
	void		update(sf::Time dt);
	void		handleEvent(sf::Event& event);
	void		draw();

	void		popScene();
	void		pushScene(Scenes::ID);
	void		clearScenes();
	
	bool		isEmpty();

	template <typename T>
	void registerScene(Scenes::ID);

private:
	void applyPendingChanges();
	Scene::Ptr	createScene(Scenes::ID );
	struct PendingChange
	{
		explicit		PendingChange(Action action, Scenes::ID sceneID = Scenes::None);

		Action			action;
		Scenes::ID		sceneID;
	};
	std::vector<Scene::Ptr>								mStack;				// holds stack of active states
	std::map<Scenes::ID, std::function<Scene::Ptr()>>	mFactories;			// holds map of functions that creates specified scenes
	Scene::Context										mContext;
	
	std::vector<PendingChange>							mPendingList;
	
};

template <typename T>
void SceneStack::registerScene(Scenes::ID sceneID)
{
	mFactories[sceneID] = [this] ()
	{
		return Scene::Ptr(new T(*this, mContext));
	};
}