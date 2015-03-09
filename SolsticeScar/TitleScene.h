#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include "Scene.h"
#include "SpriteAnim.h"
#include <array>
#include <map>
#include <functional>
class SceneStack;

class TitleScene : public Scene
{
	enum Options
	{
		Play,
		Controls,
		Quit,
		Size
	};


	// Buttons
	sf::RectangleShape		mPlayButton;
	sf::RectangleShape		mControlsButton;
	sf::RectangleShape		mQuitButton;

	int	mCurrentSelection;
	void selectNext();
	void selectPrevious();
	bool buttonsAreVisible;
	bool buttonSelected;
	std::map<int, std::function<void()>> mSelectionFunctions;

	// Button logic
	bool					playGameSelected;
	bool					quitGameSelected;
	bool					controlsSelected;

	// Controls screen
	sf::Texture				mControlsTexture;
	sf::RectangleShape		mControlsScreen;
	// Music variables
	sf::Music				mMusic;
	std::string				mFilename;
	
	// Game title font and text variables
	sf::Text				mText;
	sf::Font				mFont;


	sf::Texture				mDojiTexture;
	sf::RectangleShape		mDojiSprite;
	
	sf::Texture				mBackgroundTexture;
	sf::RectangleShape		mBackgroundSprite;
	
	
	SpriteAnim				anim;

	
	int						flipScale;
	float					scaleRate;
	float					scaleAmount;

	float					flashTimer;
	sf::RectangleShape		mWhiteFlash;
	bool					isFadeInComplete;
	float					fadeInTimer;
	sf::RectangleShape		fadeInSprite;


	void					showButtons();
public:
					TitleScene(SceneStack& stack, Context context);
	virtual bool	handleEvent(sf::Event& event);
	virtual bool	handleInput(sf::Event& event);

	virtual bool	update(sf::Time dt);
	virtual void	draw();
	
};