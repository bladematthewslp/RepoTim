#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include "Scene.h"
#include "SpriteAnim.h"


class TitleScene : public Scene
{
	sf::Music				mMusic;
	std::string				mFilename;
	bool					playGameSelected;
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

	float					fadeInTimer;
	sf::RectangleShape		fadeInSprite;
public:
					TitleScene(SceneStack& stack, Context context);
	virtual bool	handleEvent(sf::Event& event);
	virtual bool	handleInput(sf::Event& event);

	virtual bool	update(sf::Time dt);
	virtual void	draw();
	
};