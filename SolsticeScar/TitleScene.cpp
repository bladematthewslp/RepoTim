#include "TitleScene.h"
#include "SceneStack.h"

#include <iostream>


TitleScene::TitleScene(SceneStack& stack, Context& context)
	: Scene(stack, stack.mContext)
	, anim(sf::IntRect(800,0,800,336),8, 15, true, 1.6, 0)
	, mMusic()
	, mSelectionFunctions()
{

	
	// setup functions for buttons
	mSelectionFunctions[Options::Play] =		[&] () { playGameSelected = true; buttonSelected = true; };
	mSelectionFunctions[Options::Controls] =	[&] () { controlsSelected = true; };
	mSelectionFunctions[Options::Quit] =		[&] () { quitGameSelected = true; buttonSelected = true;};

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
	
	
	mFont.loadFromFile("Fonts/Chiller.ttf");

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
	
	// controls screen
	mControlsTexture.loadFromFile("Sprites/Controls.png");
	mControlsScreen.setTexture(&mControlsTexture);
	mControlsScreen.setSize(sf::Vector2f(960,600));
	mControlsScreen.setPosition(32,60);

	mLogoTexture.loadFromFile("Sprites/logo1.png");
	mLogo.setTexture(&mLogoTexture);
	mLogo.setSize(sf::Vector2f(620,304));
	mLogo.setPosition(240,20);

	mLogoTexture2.loadFromFile("Sprites/logo2.png");
	mLogo2.setTexture(&mLogoTexture2);
	mLogo2.setSize(sf::Vector2f(620,304));
	mLogo2.setPosition(240,20);

	sf::Color logo2Color = mLogo2.getFillColor();
	logo2Color.a = 0;
	mLogo2.setFillColor(logo2Color);

	firstLogoSolid = true;
	logoSwitchTimer = -4;

	playGameSelected = false;
	quitGameSelected = false;
	controlsSelected = false;
	isFadeInComplete = false;

	buttonsAreVisible = false;
	buttonSelected = false;
	mCurrentSelection = 0;
}
bool TitleScene::handleEvent(sf::Event& event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		if(controlsSelected == true)
		{
			if(event.key.code == sf::Keyboard::Return)
			{
				controlsSelected = false;
				buttonSelected = false;
			}
		}
		else if(event.key.code == sf::Keyboard::Return)
		{
			if( isFadeInComplete == true && buttonsAreVisible == false)
			{
				showButtons();
			}
			else if(buttonsAreVisible == true && buttonSelected == false)
			{
				mSelectionFunctions[mCurrentSelection]();
				
			}
		}
		else if(event.key.code == sf::Keyboard::Up && buttonSelected == false  && buttonsAreVisible == true)
		{
			selectPrevious();
		}
		else if(event.key.code == sf::Keyboard::Down && buttonSelected == false  && buttonsAreVisible == true)
		{
			selectNext();
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
	if(playGameSelected == false && fadeInTimer > dt.asSeconds() * 2  && isFadeInComplete == false)
	{
		
		sf::Color color(fadeInSprite.getFillColor());
		if(color.a < 10)
		{
			color.a = 0;
			isFadeInComplete = true;
		}
		else 
			color.a -= dt.asSeconds() * 140;
		fadeInSprite.setFillColor(color);
		fadeInTimer = 0;
	}

	// fading in/out two logos
	logoSwitchTimer += dt.asSeconds();
	if( logoSwitchTimer >= .02)
	{

		if( firstLogoSolid == true)
		{
			sf::Color color(mLogo.getFillColor() );
			if(color.a < 10)
			{
				color.a = 0;
				firstLogoSolid = false;
			}
			else
				color.a -= 1;//dt.asSeconds() * 140;

			mLogo.setFillColor(color);
		
			color = mLogo2.getFillColor();
			if(color.a > 250)
			{
				color.a = 255;
			}
			else
				color.a += 1;//dt.asSeconds() * 140;

			mLogo2.setFillColor(color);
		
		}
		else
		{
		
			sf::Color color(mLogo2.getFillColor() );
			if(color.a < 10)
			{
				color.a = 0;
			}
			else
				color.a -= 1;//dt.asSeconds() * 140;

			mLogo2.setFillColor(color);
		
			color = mLogo.getFillColor();
			if(color.a > 250)
			{
				color.a = 255;
				firstLogoSolid = true;
			}
			else
				color.a += 1;//dt.asSeconds() * 140;

			mLogo.setFillColor(color);
		}

		logoSwitchTimer = 0;
	}


	if(buttonSelected == true)
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
			switch(mCurrentSelection)
			{
				
				case Options::Play:
					mMusic.stop();
					requestStackPop();
					requestStackPush(Scenes::Game);
					break;
			
				case Options::Quit:
					mMusic.stop();
					requestStackPop();
					break;

			}
			
			
		}
		

	}


	return true;
}
void TitleScene::draw()
{
	sf::RenderWindow& window = *getContext().window;
	
	window.draw(mBackgroundSprite);
	window.draw(mWhiteFlash);
	window.draw(mPlayButton);
	window.draw(mControlsButton);
	window.draw(mQuitButton);
	window.draw(mDojiSprite);
	//window.draw(mText);
	if(logoSwitchTimer >= 0)
	{
		window.draw(mLogo2);
		window.draw(mLogo);
	}
	if(controlsSelected == true) 
		window.draw(mControlsScreen);
	window.draw(fadeInSprite);
}

void TitleScene::showButtons()
{
	mPlayButton = sf::RectangleShape((sf::Vector2f(200,80)));
	mControlsButton = sf::RectangleShape(sf::Vector2f(200,80));
	mQuitButton = sf::RectangleShape(sf::Vector2f(200,80));

	mPlayButton.setTexture(&getContext().mButtonHolder->get(Buttons::PlaySelected));
	mPlayButton.setPosition(750,260);

	mControlsButton.setTexture(&getContext().mButtonHolder->get(Buttons::ControlsNormal));
	mControlsButton.setPosition(750, 380);

	mQuitButton.setTexture(&getContext().mButtonHolder->get(Buttons::QuitNormal));
	mQuitButton.setPosition(750, 500);

	buttonsAreVisible = true;
}

void TitleScene::selectNext()
{
	
	switch(mCurrentSelection)
	{
		case Options::Play:
			mPlayButton.setTexture(&getContext().mButtonHolder->get(Buttons::PlayNormal));
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
		case Options::Play:
			mPlayButton.setTexture(&getContext().mButtonHolder->get(Buttons::PlaySelected));
			break;
		case Options::Controls:
			mControlsButton.setTexture(&getContext().mButtonHolder->get(Buttons::ControlsSelected));
			break;
		case Options::Quit:
			mQuitButton.setTexture(&getContext().mButtonHolder->get(Buttons::QuitSelected));
			break;
	}

}

void TitleScene::selectPrevious()
{
	switch(mCurrentSelection)
	{
		case Options::Play:
			mPlayButton.setTexture(&getContext().mButtonHolder->get(Buttons::PlayNormal));
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
		case Options::Play:
			mPlayButton.setTexture(&getContext().mButtonHolder->get(Buttons::PlaySelected));
			break;
		case Options::Controls:
			mControlsButton.setTexture(&getContext().mButtonHolder->get(Buttons::ControlsSelected));
			break;
		case Options::Quit:
			mQuitButton.setTexture(&getContext().mButtonHolder->get(Buttons::QuitSelected));
			break;
	}
}