#pragma once

#include <SFML/Graphics.hpp>
#include "SceneIdentifier.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

class SceneStack;

class Scene
{


public:
	
	typedef std::unique_ptr<Scene> Ptr;
	
	struct Context
	{

		Context(sf::RenderWindow& window) : window(&window), redOrbCount(0), mButtonHolder(nullptr)
		{ 
			mButtonHolder = std::unique_ptr<ButtonHolder>(new ButtonHolder()).release();
			mButtonHolder->load(Buttons::PlayNormal,		"Buttons/PlayNormal.png");
			mButtonHolder->load(Buttons::PlaySelected,		"Buttons/PlaySelected.png");
			mButtonHolder->load(Buttons::ControlsNormal,	"Buttons/ControlsNormal.png");
			mButtonHolder->load(Buttons::ControlsSelected,	"Buttons/ControlsSelected.png");
			mButtonHolder->load(Buttons::QuitNormal,		"Buttons/QuitNormal.png");
			mButtonHolder->load(Buttons::QuitSelected,		"Buttons/QuitSelected.png");
			mButtonHolder->load(Buttons::ResumeNormal,		"Buttons/ResumeNormal.png");
			mButtonHolder->load(Buttons::ResumeSelected,	"Buttons/ResumeSelected.png");
		};

		sf::RenderWindow* window;
		ButtonHolder*			mButtonHolder;
		int redOrbCount;
	};

					Scene(SceneStack& stack, Context& context);
	virtual void	draw() = 0;
	virtual bool	update(sf::Time dt) = 0;
	virtual bool	handleEvent(sf::Event& event) = 0;
	virtual bool	handleInput(sf::Event& event) = 0;
	Context&		getContext();
protected:
	void requestStackPop();
	void requestStackPush(Scenes::ID stateID);
	void requestStackClear();
	

//private:
	SceneStack*	mStack;
	Context		mContext;


};