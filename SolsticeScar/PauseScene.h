#pragma once

#include <SFML\Graphics.hpp>
#include "Scene.h"
#include <map>
#include <functional>

namespace Options
{
	enum
	{
		Resume,
		Controls,
		Quit,
		Size
	};
}

class PauseScene : public Scene
{
	

	// Buttons
	sf::RectangleShape		mResumeButton;
	sf::RectangleShape		mControlsButton;
	sf::RectangleShape		mQuitButton;

	int	mCurrentSelection;
	void selectNext();
	void selectPrevious();
	bool buttonsAreVisible;
	std::map<int, std::function<void()>> mSelectionFunctions;

	// Button logic
	bool					resumeGameSelected;
	bool					quitGameSelected;
	bool					controlsSelected;

	// Controls screen
	sf::Texture				mControlsTexture;
	sf::RectangleShape		mControlsScreen;


	sf::Texture				mRedOrbTexture;
	sf::Font				mFont;
	sf::Text				mText;
	sf::Color				mTextColor;
	sf::RectangleShape		mShape;
public:
	PauseScene(SceneStack& stack, Context& context);

	bool			handleEvent(sf::Event& event);
	bool			handleInput(sf::Event& event);
	bool			update(sf::Time dt);
	void			draw();
	std::string convertIntToString(int num);
};