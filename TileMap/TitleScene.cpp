#include "TitleScene.h"

#include <iostream>


TitleScene::TitleScene(SceneStack& stack, Context context)
	: Scene(stack, context)
	, anim(sf::IntRect(800,0,800,336),8, 15, true, 1.6, 0)
	, mMusic()
{
	// reset the view
	sf::Vector2f centerPoint(context.window->getSize().x/2, context.window->getSize().y/2);
	sf::Vector2f windowSize(context.window->getSize().x, context.window->getSize().y);
	context.window->setView(sf::View(centerPoint, windowSize));

	// setup intro music
	mFilename = "Music/IntroMusic.ogg";
	// Open it from an audio file
	if (!mMusic.openFromFile(mFilename))
	{
		throw std::runtime_error("Music " + mFilename + " could not be loaded.");
	}
	mMusic.setLoop(true);        
	// Play it
	mMusic.play();
	
	
	mFont.loadFromFile("Chiller.ttf");

	mBackgroundSprite.setSize(sf::Vector2f(context.window->getSize().x + 75, context.window->getSize().y + 25));//sf::Vector2f(100,100));

	mText.setFont(mFont);
	mText.setColor(sf::Color(200,200,200,255));//::White);
	mText.setString("SOLSTICE\nSCAR");
	mText.setCharacterSize(110);
	mText.setPosition(310,80);//context.window->getView().getSize() / 2.f);
	
	
	// Doji Texture and Sprite
	mDojiTexture.loadFromFile("Sprites/TitleScreen/DojiTitleScreen.png");
	mDojiSprite.setSize(sf::Vector2f(1024,720));
	mDojiSprite.setTexture(&mDojiTexture);
	mDojiSprite.setPosition(-60,0);

	// Background Texture and Sprite
	mBackgroundTexture.loadFromFile("Sprites/TitleScreen/RainingBackgroundSpriteSheetCropped.png");
	mBackgroundSprite.setTexture(&mBackgroundTexture);
	mBackgroundSprite.setPosition(0,0);
	// backgroud scaling variables
	flipScale = 1;
	scaleRate = 0.00005;
	scaleAmount = 1;

	mWhiteFlash.setSize(sf::Vector2f(2000,2000));
	sf::Color color(sf::Color::White);
	color.a = 0;
	mWhiteFlash.setFillColor(color);
	mWhiteFlash.setPosition(0,0);
	flashTimer = 0;

	fadeInTimer = 0;
	fadeInSprite.setSize(sf::Vector2f(2000,2000));
	fadeInSprite.setFillColor(sf::Color::Black);
	
	playGameSelected = false;
}
bool TitleScene::handleEvent(sf::Event& event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		sf::Color color = fadeInSprite.getFillColor();
		if(playGameSelected == false && color.a != 0)
		{
			color.a = 0;
			fadeInSprite.setFillColor(color);
		}
		else
		{
			if( playGameSelected == false)
				playGameSelected = true;
		}
	}
	
	return true;
}

bool TitleScene::handleInput(sf::Event& event)
{
	return true;
}

bool TitleScene::update(sf::Time dt)
{

	// background scaling and playing
	scaleAmount += scaleRate;
	if(scaleAmount > 1.01 || scaleAmount < 0.99)
		scaleRate *= -1;
	
	mBackgroundSprite.setScale(scaleAmount,scaleAmount);
	anim.run(mBackgroundSprite);

	// white flashing
	flashTimer += dt.asSeconds();
	if(flashTimer > 4.19)
	{
		sf::Color color(sf::Color::White);
		color.a = 0;
		mWhiteFlash.setFillColor(color);
		flashTimer = 0;
	}
	else if(flashTimer > 4)
	{
		sf::Color color(sf::Color::White);
		color.a = 98;
		mWhiteFlash.setFillColor(color);
	}
	
	// black fading in
	fadeInTimer += dt.asSeconds();
	if(playGameSelected == false && fadeInTimer > dt.asSeconds() * 2 )
	{
		
		sf::Color color(fadeInSprite.getFillColor());
		if(color.a < 10)
			color.a = 0;
		else 
			color.a -= dt.asSeconds() * 140;
		fadeInSprite.setFillColor(color);
		fadeInTimer = 0;
	}

	if(playGameSelected == true)
	{
		sf::Color color = fadeInSprite.getFillColor();
		if(color.a < 250)
		{
			color.a += dt.asSeconds() * 140;
			fadeInSprite.setFillColor(color);
		}
		else
		{
			color.a = 255;
			mMusic.stop();
			requestStackPop();
			requestStackPush(Scenes::Game);
		}

	}


	return true;
}
void TitleScene::draw()
{
	sf::RenderWindow& window = *getContext().window;
	
	window.draw(mBackgroundSprite);
	window.draw(mWhiteFlash);
	window.draw(mDojiSprite);
	window.draw(mText);
	window.draw(fadeInSprite);
}