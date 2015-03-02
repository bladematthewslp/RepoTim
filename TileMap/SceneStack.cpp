#include "SceneStack.h"
#include "Foreach.hpp"
#include <cassert>
SceneStack::SceneStack(Scene::Context context)
	: mStack()
	, mFactories()
	, mContext(context)
	, mPendingList()
{
	
}

void SceneStack::handleEvent(sf::Event& event)
{

	for(auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if( !(*itr)->handleEvent(event))
			break;
	}

	applyPendingChanges();
}

void SceneStack::handleInput(sf::Event& event)
{
	for(auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if( !(*itr)->handleInput(event))
			break;
	}
}
void SceneStack::update(sf::Time dt)
{
	for(auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if( !(*itr)->update(dt))
			break;
	}

	applyPendingChanges();

}
void SceneStack::draw()
{
	FOREACH(Scene::Ptr& state, mStack)
		state->draw();

}
void SceneStack::popScene()
{
	mPendingList.push_back(PendingChange(Pop));
}

void SceneStack::pushScene(Scenes::ID sceneID)
{
	
	mPendingList.push_back(PendingChange(Action::Push, sceneID));
}

void SceneStack::clearScenes()
{
	mPendingList.push_back(PendingChange(Action::Clear));
}
bool SceneStack::isEmpty()
{
	return mStack.empty();
}

void SceneStack::applyPendingChanges()
{
	FOREACH(PendingChange change, mPendingList)
	{
		switch(change.action)
		{
		case Push:
			mStack.push_back(createScene(change.sceneID));
			break;

		case Pop:
			mStack.pop_back();
			break;

		case Clear:
			mStack.clear();
			break;
		}
		

	}

	mPendingList.clear();
}

Scene::Ptr	SceneStack::createScene(Scenes::ID stateID)
{
	auto found = mFactories.find(stateID);
	
	assert(found != mFactories.end());
	return found->second();

}

SceneStack::PendingChange::PendingChange(Action action, Scenes::ID sceneID)
	: action(action)
	, sceneID(sceneID)
{
}