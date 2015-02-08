#pragma once

#include <SFML/Graphics.hpp>
#include "SceneIdentifier.h"


class SceneStack;

class Scene
{


public:
	
	typedef std::unique_ptr<Scene> Ptr;
	
	struct Context
	{
		Context(sf::RenderWindow& window) : window(&window){};

		sf::RenderWindow* window;
	};

					Scene(SceneStack& stack, Context context);
	virtual void	draw() = 0;
	virtual bool	update(sf::Time dt) = 0;
	virtual bool	handleEvent(sf::Event& event) = 0;
	virtual bool	handleInput(sf::Event& event) = 0;

protected:
	void requestStackPop();
	void requestStackPush(Scenes::ID stateID);
	void requestStackClear();
	Context		getContext() const;

private:
	SceneStack*	mStack;
	Context		mContext;


};