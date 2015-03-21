#include "PauseScene.h"
#include "SceneStack.h"
#include "System.h"
#include "World.h"
#include <iostream>
#include <sstream>
#include <string>

std::string PauseScene::convertIntToString(int num)
{
	int number = num;       // number to be converted to a string
	std::string result;          // string which will contain the result
	std::ostringstream convert;   // stream used for the conversion
	convert << number;      // insert the textual representation of 'Number' in the characters in the stream
	result = convert.str(); // set 'Result' to the contents of the stream
	return result;
}

PauseScene::PauseScene(SceneStack& stack, Context& context)
	: Scene(stack, stack.mContext)
	, mShape(sf::Vector2f(27,45))
	, mTextColor(sf::Color(232,43,1,255))
{

	mRedOrbTexture.loadFromFile("Sprites/red_orb.png");
	
	mShape.setTexture(&mRedOrbTexture);
	//mShape.setFillColor(sf::Color::Magenta);
	sf::Vector2f viewOrigin;
	viewOrigin.x = getContext().window->getView().getCenter().x - getContext().window->getSize().x/2;
	viewOrigin.y = getContext().window->getView().getCenter().y - getContext().window->getSize().y/2;
	mShape.setPosition(viewOrigin + sf::Vector2f(875,20));

	// load font
	mFont.loadFromFile("Fonts/CHILLER.ttf");
	getContext().redOrbCount;

	// initialize text
	mText.setFont(mFont);
	int i = getContext().redOrbCount;
	std::string numOrbs = convertIntToString(i);
	mText.setString("x" + numOrbs);
	mText.setPosition( viewOrigin + sf::Vector2f(910,30));
	mText.setColor(mTextColor);
	mText.setStyle(sf::Text::Bold);

	// setup functions for buttons
	mSelectionFunctions[Options::Resume] =		[&] () { requestStackPop(); };
	mSelectionFunctions[Options::Controls] =	[&] () { controlsSelected = true; };
	mSelectionFunctions[Options::Quit] =		[&] () { System::mWorld->cleanupWorld(); requestStackClear(); requestStackPush(Scenes::Title); };

	mResumeButton = sf::RectangleShape((sf::Vector2f(200,80)));
	mControlsButton = sf::RectangleShape(sf::Vector2f(200,80));
	mQuitButton = sf::RectangleShape(sf::Vector2f(200,80));

	mResumeButton.setTexture(&getContext().mButtonHolder->get(Buttons::ResumeSelected));
	mResumeButton.setPosition(viewOrigin + sf::Vector2f(750,300));

	mControlsButton.setTexture(&getContext().mButtonHolder->get(Buttons::ControlsNormal));
	mControlsButton.setPosition(viewOrigin + sf::Vector2f(750, 420));

	mQuitButton.setTexture(&getContext().mButtonHolder->get(Buttons::QuitNormal));
	mQuitButton.setPosition(viewOrigin + sf::Vector2f(750, 540));

	// controls screen
	mControlsTexture.loadFromFile("Sprites/Controls.png");
	mControlsScreen.setTexture(&mControlsTexture);
	mControlsScreen.setSize(sf::Vector2f(960,600));
	mControlsScreen.setPosition(viewOrigin + sf::Vector2f(32,60));

	mCurrentSelection = 0;
	resumeGameSelected = false;
	quitGameSelected = false;
	controlsSelected = false;
}

bool PauseScene::handleEvent(sf::Event& event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		if(controlsSelected == true)
		{
			controlsSelected = false;
		}
		else if(event.key.code == sf::Keyboard::Down)
		{
			selectNext();
		}
		else if(event.key.code == sf::Keyboard::Up)
		{
			selectPrevious();
		}
		else if(event.key.code == sf::Keyboard::Return)
		{
			mSelectionFunctions[mCurrentSelection]();
		}
	}
	return false;
}

bool PauseScene::handleInput(sf::Event& event)
{

	return false;
}

bool PauseScene::update(sf::Time dt)
{
	
	return false;
}

void PauseScene::draw()
{
	sf::RenderWindow& window = *getContext().window;

	//window.draw(mShape);
	window.draw(mText);
	window.draw(mShape);
	window.draw(mResumeButton);
	window.draw(mControlsButton);
	window.draw(mQuitButton);
	if(controlsSelected == true)
		window.draw(mControlsScreen);
}

void PauseScene::selectNext()
{
	
	switch(mCurrentSelection)
	{
		case Options::Resume:
			mResumeButton.setTexture(&getContext().mButtonHolder->get(Buttons::ResumeNormal));
			break;
		case Options::Controls:
			mControlsButton.setTexture(&getContext().mButtonHolder->get(Buttons::ControlsNormal));
			break;
		case Options::Quit:
			mQuitButton.setTexture(&getContext().mButtonHolder->get(Buttons::QuitNormal));
			break;
	}

	
	mCurrentSelection++;
	if(mCurrentSelection >= Options::Size)
	{
		mCurrentSelection = 0;
	}
	
	switch(mCurrentSelection)
	{
		case Options::Resume:
			mResumeButton.setTexture(&getContext().mButtonHolder->get(Buttons::ResumeSelected));
			break;
		case Options::Controls:
			mControlsButton.setTexture(&getContext().mButtonHolder->get(Buttons::ControlsSelected));
			break;
		case Options::Quit:
			mQuitButton.setTexture(&getContext().mButtonHolder->get(Buttons::QuitSelected));
			break;
	}

}

void PauseScene::selectPrevious()
{
	switch(mCurrentSelection)
	{
		case Options::Resume:
			mResumeButton.setTexture(&getContext().mButtonHolder->get(Buttons::ResumeNormal));
			break;
		case Options::Controls:
			mControlsButton.setTexture(&getContext().mButtonHolder->get(Buttons::ControlsNormal));
			break;
		case Options::Quit:
			mQuitButton.setTexture(&getContext().mButtonHolder->get(Buttons::QuitNormal));
			break;
	}

	
	mCurrentSelection--;
	if(mCurrentSelection < 0)
	{
		mCurrentSelection = Options::Size - 1;
	}
	
	switch(mCurrentSelection)
	{
		case Options::Resume:
			mResumeButton.setTexture(&getContext().mButtonHolder->get(Buttons::ResumeSelected));
			break;
		case Options::Controls:
			mControlsButton.setTexture(&getContext().mButtonHolder->get(Buttons::ControlsSelected));
			break;
		case Options::Quit:
			mQuitButton.setTexture(&getContext().mButtonHolder->get(Buttons::QuitSelected));
			break;
	}
}