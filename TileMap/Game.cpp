

#include <iostream>
#include "Game.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "PauseScene.h"
//#include "Component.h"
//#include "GameObject.h"
//#include "Command.h"
//#include "GameObjectManager.h"
//#include "System.h"
//#include "PlayerRender.h"
//#include "PlayerLogic.h"
//#include "PlayerInput.h"
//#include "NinjaRender.h"
//#include "BoxColliderComponent.h"
//#include "NinjaLogic.h"
#include "Scene.h"
#include <array>

const sf::Time TimePerFrame = sf::seconds(1.0f/60.0f);


Game::Game() 
	: mWindow(sf::VideoMode(1024, 720,32), "TileMap")
	//, mWorldView(sf::FloatRect(0,0,1024,720))//mWindow.getDefaultView())
	, worldWidth(1024)
	, worldHeight(720)
	, mWorldBounds(0.0f, 0.0f, 1024.f, 720.f)
	//, mGameObjectManager()
	//, grid()
	//, mPlayer(GameObjectDesc("Player", sf::RectangleShape(), Layer::Player))
	, mSceneStack(Scene::Context(mWindow))
{
	sf::ContextSettings settings = mWindow.getSettings();
	std::cout << settings.majorVersion << "." << settings.minorVersion << std::endl;
	mWindow.setKeyRepeatEnabled(false);

	registerScenes();
	mSceneStack.pushScene(Scenes::Title);

	/*
	mPlayer.addComponent(ComponentType::RenderComponent, std::unique_ptr<Component>(new PlayerRender(&mPlayer)).release());
	mPlayer.addComponent(ComponentType::LogicComponent, std::unique_ptr<Component>(new PlayerLogic(&mPlayer)).release());// std::unique_ptr<Component>(new Player(&mPlayer)).release());
	mPlayer.addComponent(ComponentType::InputComponent, std::unique_ptr<Component>(new PlayerInput(&mPlayer)).release());
	
	// Box Collider Component
		mPlayer.addComponent(ComponentType::BoxColliderComponent, std::unique_ptr<Component>(new BoxColliderComponent(&mPlayer)).release());
		mPlayer.mBoxColliderComponent->setSize(80, 98);
		//mPlayer.mBoxColliderComponent->setVisible(true);
	*/
	/*
	GameObject* newObject = std::unique_ptr<GameObject>(new GameObject(GameObjectDesc("second",sf::RectangleShape(sf::Vector2f(20,1)), 
																						Layer::Enemy,
																						ComponentType::RenderComponent | 
																						ComponentType::BoxColliderComponent))).release();
	newObject->setPosition(sf::Vector2f(450,515));
	newObject->addComponent(ComponentType::LogicComponent,std::unique_ptr<Component>(new BoxColliderComponent(newObject)).release());
	*/
	
	/*
	GameObjectDesc ninjaDesc("Ninja",sf::RectangleShape(), Layer::Enemy,ComponentType::LogicComponent);
	GameObject* ninja = std::unique_ptr<GameObject>(new GameObject(ninjaDesc)).release();
	ninja->setPosition(700,475);

	ninja->addComponent(ComponentType::RenderComponent, std::unique_ptr<Component>(new NinjaRender(ninja)).release());
	ninja->addComponent(ComponentType::LogicComponent, std::unique_ptr<Component>(new NinjaLogic(ninja)).release());
	ninja->addComponent(ComponentType::BoxColliderComponent, std::unique_ptr<Component>(new BoxColliderComponent(ninja)).release());
	ninja->mBoxColliderComponent->setSize(50,75);
	//ninja->mBoxColliderComponent->setVisible(true);

	GameObjectDesc backgroundDesc("Forest",sf::RectangleShape(sf::Vector2f(2048,720)),Layer::Background,ComponentType::RenderComponent);
	GameObject* background = std::unique_ptr<GameObject>(new GameObject(backgroundDesc)).release();
	background->mRenderComponent->mImage.loadFromFile("Sprites/jungle_background.png");
	background->mRenderComponent->mTexture.loadFromImage(background->mRenderComponent->mImage);
	background->mRenderComponent->mSprite.setTexture(&background->mRenderComponent->mTexture);
	background->setPosition(0,0);


	mWorldView.setCenter(300,300);

	init();
	*/
}


void Game::init()
{
	//System::init();
	//mGameObjectManager.init();
	
	//std::cout << " " << System::mGameObjects.at(0)->mName  << " " << std::endl;
}



void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
		
	while(mWindow.isOpen() )
	{
		
			sf::Event event;
			timeSinceLastUpdate += clock.restart();
			while(timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;
				handleEvent(event);
				handleInput(event);
				update(TimePerFrame);
				//System::handleInput(mWindow, grid, event);
				//System::update(grid, TimePerFrame, mGameObjectManager);
				//mPlayer.update(&grid, event, TimePerFrame);
				if(mSceneStack.isEmpty())
					mWindow.close();
			}
		
			render();
	}
}

void Game::handleEvent(sf::Event& event)
{
	
	while(mWindow.pollEvent(event))
	{
		
		mSceneStack.handleEvent(event);

		if(event.type == sf::Event::Closed)
			mWindow.close();
		
	}
}

void Game::handleInput(sf::Event& event)
{
	mSceneStack.handleInput(event);
}
void Game::update(sf::Time dt)
{
	mSceneStack.update(dt);
}
void Game::render()
{
	mWindow.clear(sf::Color(62,98,135));
	//mWindow.clear();
	mSceneStack.draw();
	//mWindow.setView(mWindow.getDefaultView());
	mWindow.display();
	//mWindow.clear(sf::Color(155,155,155));
	//grid.draw(mWindow);
	
	//bBox->setSize(sf::Vector2f(mPlayer.getSprite().getGlobalBounds().width/2, mPlayer.getSprite().getGlobalBounds().height/2));
	//bBox->setPosition(mPlayer.getPosition().x, mPlayer.getPosition().y + mPlayer.getSprite().getGlobalBounds().height/4);
	//mWindow.draw(*bBox);
	//mWindow.draw(mPlayer.playerBBox);
	//mPlayer.draw(mWindow);

	//testObject.move(.2,.2);
	//testObject.mRenderComponent->Update();
	//mWorldView.setCenter(sf::Vector2f( (mPlayer.getPosition().x < 512 ? 512 : mPlayer.getPosition().x), 360));
	//mWindow.setView(mWorldView);
	
	//System::render(mWindow, mGameObjectManager);
	//mSystem.update(mWindow);
	
	//mWindow.display();
}

void Game::registerScenes()
{
	mSceneStack.registerScene<TitleScene>(Scenes::Title);
	mSceneStack.registerScene<GameScene>(Scenes::Game);
	mSceneStack.registerScene<PauseScene>(Scenes::Pause);
}


/*
void Game::drawGrid(sf::RenderWindow& window)
{
	sf::RectangleShape block(sf::Vector2f(30,30) );

	for(int i = 0; i < grid.mGrid.size(); i++)
	{
		for(int j = 0; j < grid.mGrid.size(); j++)
		{
			//if(grid.mGrid[j][i] == 1)
			{
				block.setFillColor(sf::Color::Red);
			}
			//else
			{
				block.setFillColor(sf::Color::Green);
			}
				block.setPosition(i * 32, j*32);
				window.draw(block);
		}
	}
}

*/

