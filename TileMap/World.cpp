#include "World.h"
#include "System.h"
#include "PlayerRender.h"
#include "PlayerLogic.h"
#include "PlayerInput.h"
#include "PlayerBoxCollider.h"
#include "NinjaGameObject.h"
#include "BackgroundGameObject.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "RenderComponent.h"
#include "HealthBarLogic.h"
#include "GUIRedOrbLogic.h"
#include "GUIRedOrbRender.h"
#include "RyobeGameObject.h"
#include "ItemGameObject.h"
#include "NinjaLogic.h"

#include "BattleReadyState.h"
#include "CStateRyobeBattleEntrance.h"
#include "WinState.h"

#include <iostream>
World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(sf::FloatRect(0,0, 1024, 720))
	, mWorldBounds(0.0f, 0.0f, 5080.0f, 720.f)
	, mWorldWidth(1024)
	, mWorldHeight(720)
	, mFadeOutShape(sf::Vector2f(2000,2000))
{
	// init stuff here
	RenderComponent::loadImages();
	System::init();
	Attacks::registerAttacks();

	// ___________________________________
	//	GUI Setup
	// ___________________________________
	
	
	/*
	// Mugshot
	GameObjectDesc mugshotDesc(	"Mugshot",sf::RectangleShape(sf::Vector2f(90,120)),	Layer::UI,	ComponentType::RenderComponent);
	GameObject* mugshot = std::unique_ptr<GameObject>(new GameObject(mugshotDesc)).release();
	mugshot->setPosition(15, 10);
	mugshot->setPosition(sf::Vector2f());
	mugshot->mRenderComponent->mSprite.setTexture(&mugshot->getRenderComponent()->mTextureHolder.get(Textures::PlayerMugshot));
	*/
	// GUI Red Orb
	GameObjectDesc GUIRedOrbDesc("GUIRedOrb", sf::RectangleShape(sf::Vector2f(27,45)), Layer::UI);
	GUIRedOrb = std::unique_ptr<GameObject>(new GameObject(GUIRedOrbDesc)).release();
	GUIRedOrb->addComponent(ComponentType::RenderComponent, std::unique_ptr<Component>(new GUIRedOrbRender(GUIRedOrb)).release());
	GUIRedOrb->addComponent(ComponentType::LogicComponent, std::unique_ptr<Component>(new GUIRedOrbLogic(GUIRedOrb)).release());

	GameObjectDesc healthBarDesc("HealthBar", sf::RectangleShape(sf::Vector2f(225,20)), Layer::UI, ComponentType::RenderComponent);
	mHealthBar = std::unique_ptr<GameObject>(new GameObject(healthBarDesc)).release();
	mHealthBar->addComponent(ComponentType::LogicComponent, std::unique_ptr<Component>(new HealthBarLogic(mHealthBar)).release());
	mHealthBar->setPosition(170, 82);
	//mHealthBar->mRenderComponent->mIsEnabled = false;

	GameObjectDesc playerHUDDesc("PlayerHUD", sf::RectangleShape(sf::Vector2f(407,136)), Layer::UI, ComponentType::RenderComponent);
	GameObject* playerHUD = std::unique_ptr<GameObject>(new GameObject(playerHUDDesc)).release();
	playerHUD->setPosition(15, 10);
	playerHUD->setPosition(sf::Vector2f());
	playerHUD->mRenderComponent->mSprite.setTexture(&playerHUD->getRenderComponent()->mTextureHolder.get(Textures::PlayerHUD));

	
	mGrid = std::unique_ptr<Grid>(new Grid()).release();

	// Add the background sprite to the scene
	GameObjectDesc backgroundDesc(	"Background", 
									sf::RectangleShape(sf::Vector2f(1024, 720)), 
									Layer::Background, 
									ComponentType::RenderComponent);
	GameObjectDesc foregroundDesc(	"Foreground", 
									sf::RectangleShape(sf::Vector2f(1024, 720)), 
									Layer::Foreground, 
									ComponentType::RenderComponent);

	
	for(int i = 0; i < 6; i++)
	{
		mBackground[i] = std::unique_ptr<GameObject>(new BackgroundGameObject(backgroundDesc)).release();
		mBackground[i]->setPosition( i * 1024, 0);

		/*mForeground[i] = std::unique_ptr<GameObject>(new GameObject(foregroundDesc)).release();
		//mForeground[i]->mRenderComponent->mTexture = RenderComponent::mTextureHolder.get(Textures::WoodsForeground);
		mForeground[i]->mRenderComponent->mSprite.setTexture(&RenderComponent::mTextureHolder.get(Textures::WoodsForeground));
		mForeground[i]->setPosition( i * 1024, 0);*/
	}
	
	

	mPlayer = std::unique_ptr<GameObject>(new GameObject(GameObjectDesc("Player", sf::RectangleShape(), Layer::Player))).release();
	mPlayer->addComponent(ComponentType::RenderComponent, std::unique_ptr<Component>(new PlayerRender(mPlayer)).release());
	mPlayer->addComponent(ComponentType::LogicComponent, std::unique_ptr<Component>(new PlayerLogic(mPlayer)).release());// std::unique_ptr<Component>(new Player(&mPlayer)).release());
	mPlayer->addComponent(ComponentType::InputComponent, std::unique_ptr<Component>(new PlayerInput(mPlayer)).release());
	// Box Collider Component
	mPlayer->addComponent(ComponentType::BoxColliderComponent, std::unique_ptr<Component>(new PlayerBoxCollider(mPlayer)).release());
	mPlayer->mBoxColliderComponent->setSize(80, 98);
		//mPlayer->mBoxColliderComponent->setVisible(true);

	
	
	GameObjectDesc ninjaDesc("Ninja",sf::RectangleShape(), Layer::Enemy);//,ComponentType::LogicComponent);
	// make 4 ninjas
	ninjaGameObjects.reserve(4);
	for(int i = 0; i < 4; i++)
	{
		GameObject* ninja = std::unique_ptr<GameObject>(new NinjaGameObject(ninjaDesc)).release();
		ninja->mBoxColliderComponent->setSize(50,75);
		ninja->setPosition( 3600 + (300*i),536);
		ninjaGameObjects.push_back(ninja);
	}
	GameObjectDesc ryobeDesc("Ryobe",sf::RectangleShape(), Layer::Enemy);
	ryobeGameObject = std::unique_ptr<GameObject>(new RyobeGameObject(ryobeDesc)).release();
	//ryobeGameObject->setPosition(100, 568);
	ryobeGameObject->setPosition(-1000, -1000);
	
	mLookAtPoint = sf::Vector2f(mPlayer->getPosition().x, 360);
	scrollableWorld = true;
	playerReachedBossFightLocation = false;
	bossFightStarted = false;
	xPositionBossFightStart = 4000;
	timerToBeginBattle = 0;
	startTimerToBeginBattle = false;
	lightningWallLeft  = nullptr;
	lightningWallRight = nullptr;
	
	bossDefeated = false;
	timerToStartPlayerWinPose = 0;

	sf::Color black = sf::Color::Black;
	black.a = 0;
	mFadeOutShape.setFillColor(black);
}

bool World::handleEvent(sf::RenderWindow& window, sf::Event& event)
{
	if(event.key.code == sf::Keyboard::U)
	{
		GameObject* f = System::findGameObjectByName("redBlock");
		System::removeGameObject(f);
	}
	System::handleEvent(window, event);
	//std::cout << "WORLD HANDLE EVENT" << std::endl;

	if(event.type == sf::Event::MouseButtonPressed)
	{
		sf::Vector2i pos = mWindow.mapCoordsToPixel(sf::Vector2f(sf::Mouse::getPosition(mWindow)),mWindow.getDefaultView());
		std::cout << (int)(pos.x + mWorldView.getCenter().x - 512)/32 << "," << pos.y/32 << std::endl;
	}
	return true;
}

bool World::handleInput(sf::Event& event)
{
	System::handleInput(event);
	return true;
}

bool World::update(sf::Time dt)
{
	destroyGameObjectsOutsideView();

	// if player is in the range of battle
	if(playerReachedBossFightLocation == false 
		&& mPlayer->getPosition().x >  xPositionBossFightStart && mPlayer->getPosition().x < xPositionBossFightStart + 100 )
	{
		// check if all ninjas are dead
		int count = 0;
  		for(int i = 0; i < ninjaGameObjects.size(); i++)
		{
			
			if( dynamic_cast<NinjaLogic*>(ninjaGameObjects.at(i)->mLogicComponent)->getHealth() <= 0 )
			{
				count++;
			}
		}

		// if all ninjas are dead, remove them from game
		if(count == ninjaGameObjects.size() )
		{
			while(ninjaGameObjects.size() != 0)
			{
				
				System::removeGameObject( ninjaGameObjects.back() );
				ninjaGameObjects.pop_back();
			}
			playerReachedBossFightLocation = true;

		}
		
	}

	// once player reaches fight location and all ninjas are dead...
	if(playerReachedBossFightLocation == true && startTimerToBeginBattle == false && bossFightStarted == false)
	{
		// turn world scrolling off
		scrollableWorld = false;

		// disable player input
		dynamic_cast<PlayerInput*>(mPlayer->mInputComponent)->disableInput();

		// if player is ready for battle
		if( dynamic_cast<PlayerLogic*>(mPlayer->mLogicComponent)->isReadyForBattle() == true && startTimerToBeginBattle == false)
		{
			// turn player to direction of ryobe
			dynamic_cast<PlayerLogic*>(mPlayer->mLogicComponent)->updateDirection(Direction::Right);

			// setup  lightning walls
			GameObjectDesc lightningDesc("Lightning", sf::RectangleShape(sf::Vector2f(40,680)), Layer::Default, ComponentType::RenderComponent);
			lightningWallLeft = std::unique_ptr<GameObject>(new GameObject(lightningDesc)).release();
			lightningWallLeft->mRenderComponent->createSpriteAnim(sf::IntRect(40, 0, 40, 340),"Lightning",true, 6, 1.6);
			lightningWallLeft->mRenderComponent->setAnimation("Lightning");
			lightningWallLeft->mRenderComponent->mSprite.setTexture(&RenderComponent::mTextureHolder.get(Textures::LightningWall));//lightningWallLeft->mRenderComponent->mTexture);
			lightningWallLeft->addComponent(ComponentType::BoxColliderComponent);

			lightningWallRight = std::unique_ptr<GameObject>(new GameObject(lightningDesc)).release();
			lightningWallRight->mRenderComponent->createSpriteAnim(sf::IntRect(40, 0, 40, 340),"Lightning",true, 6, 1.6);
			lightningWallRight->mRenderComponent->setAnimation("Lightning");
			lightningWallRight->mRenderComponent->mSprite.setTexture(&RenderComponent::mTextureHolder.get(Textures::LightningWall));//lightningWallRight->mRenderComponent->mTexture);
			lightningWallRight->addComponent(ComponentType::BoxColliderComponent);

			lightningWallLeft->setPosition(xPositionBossFightStart - 450,0);
			lightningWallRight->setPosition(xPositionBossFightStart + 450,0);
			startTimerToBeginBattle = true;
		}
	}
	

	// if timer to begin battle has begun
	if(startTimerToBeginBattle == true)
	{
		timerToBeginBattle += dt.asSeconds();

		// if timer reaches set number to make ryobe appear in screen
		if(timerToBeginBattle >= 3 && ryobeGameObject->mState == nullptr )
		{
			ryobeGameObject->setPosition(4300, 536);
			ryobeGameObject->mState = std::unique_ptr<CState>(new CStateRyobeBattleEntrance(ryobeGameObject)).release();
			//bossFightStarted = true;
			startTimerToBeginBattle = false;
		}
	}

	//ready the player for battle
	if(bossFightStarted == false)
	{
		if(ryobeGameObject->mState != nullptr && ryobeGameObject->mState->getName() == "CStateRyobeStanding")
		{
			//dynamic_cast<BattleReadyState*>(mPlayer->mState)->setMaxTime(1);
			
			mPlayer->mRenderComponent->setAnimation("BattleReadyEnding");
			mPlayer->mInputComponent->mIsEnabled = true;
			bossFightStarted = true;
		}
	}

	// after the boss fight begins, check if he is dead
	if(bossFightStarted == true)
	{
		if(ryobeGameObject->mState->getName() == "CStateRyobeDead")
		{
			bossDefeated = true;
			dynamic_cast<PlayerInput*>(mPlayer->mInputComponent)->disableInput();
		}

		// if boss is dead...
		if(bossDefeated == true)
		{
			timerToStartPlayerWinPose += dt.asSeconds();
			// change player state to win state
			if(timerToStartPlayerWinPose > 5 && mPlayer->mState->getName() != "WinState")
			{
				CState* newState = std::unique_ptr<CState>(new WinState(mPlayer)).release();
				dynamic_cast<PlayerLogic*>(mPlayer->mLogicComponent)->setNewState(newState);
				
			}
			// fade out when the timer reaches a set number
			else if(timerToStartPlayerWinPose > 10)
			{
				mFadeOutShape.setPosition(mWorldView.getCenter().x - mWorldView.getSize().x/2, 0);
				sf::Color color = mFadeOutShape.getFillColor();
				if(color.a > 250)
				{
					color.a = 255;
					return false;
				}
				color.a += 2.5;
				mFadeOutShape.setFillColor(color);
			}
		}
	}
	


	if(lightningWallLeft != nullptr && lightningWallRight != nullptr)
	{
		lightningWallLeft->mRenderComponent->runSpriteAnim(*lightningWallLeft);
		lightningWallRight->mRenderComponent->runSpriteAnim(*lightningWallRight);
	}


	System::update(*mGrid,dt);
	return true;
}

void World::draw(sf::RenderWindow& window)
{
	int worldViewXLimit = 512;
	int cameraLerpSpeed = 2;
	int pointToLook;
	int viewPosX = mWorldView.getCenter().x;
	int playerPosX = mPlayer->getPosition().x;

	if(playerReachedBossFightLocation == false)
	{

		if(dynamic_cast<PlayerLogic*>(mPlayer->mLogicComponent)->getDirection() == Direction::Right)
		{
		
				if(playerPosX > viewPosX + 50)
					mLookAtPoint.x += cameraLerpSpeed;
			//}
			//else if(playerPosX < viewPosX + 50)
				//mLookAtPoint.x -= cameraLerpSpeed;
		}
		else if(dynamic_cast<PlayerLogic*>(mPlayer->mLogicComponent)->getDirection() == Direction::Left)
		{
		
				if(playerPosX < viewPosX - 50)
					mLookAtPoint.x -= cameraLerpSpeed;
			//}
			//else if(playerPosX > viewPosX - 50)
				//mLookAtPoint.x += cameraLerpSpeed;
		}
	}
	else if(playerReachedBossFightLocation == true && mLookAtPoint.x != xPositionBossFightStart)
	{
		if(mLookAtPoint.x > xPositionBossFightStart )
			mLookAtPoint.x -= 1;
		else if(mLookAtPoint.x < xPositionBossFightStart )
			mLookAtPoint.x += 1;
	
	}

	if(mLookAtPoint.x < worldViewXLimit)
	{
		mLookAtPoint.x = worldViewXLimit;
	}


	
	//mWorldView.setCenter(sf::Vector2f( (mPlayer->getPosition().x < 512 ? 512 : mPlayer->getPosition().x), 360));
	//mWorldView.setCenter(mLookAtPoint);//sf::Vector2f( (mPlayer->getPosition().x < 512 ? 512 : mPlayer->getPosition().x), 360));

	//if(scrollableWorld == true)
	{
		mWorldView.setCenter(mLookAtPoint);
	}
	//else
	{
		//mWorldView.setCenter(sf::Vector2f(xPositionBossFightStart, 360));
	}

	mWindow.setView(mWorldView);
	System::draw(window);
	window.draw(mFadeOutShape);
}

void World::destroyGameObjectsOutsideView()
{
	std::array<GameObject*, 7>::iterator layer_itr;
	for(layer_itr = System::mSceneLayers.begin(); layer_itr != System::mSceneLayers.end(); layer_itr++)
	{
		if((*layer_itr)->mName == Layer::Enemy)
		{
			std::vector<GameObject*>::iterator obj_itr;
			for(obj_itr = (*layer_itr)->mChildren.begin(); obj_itr != (*layer_itr)->mChildren.end(); obj_itr++)
			{
				if((*obj_itr)->mName == "Dagger")
				{
					float dist = std::abs(mWorldView.getCenter().x - (*obj_itr)->getWorldPosition().x);
					if(dist > mWorldView.getSize().x/2)
					{
						System::removeGameObject( (*obj_itr) );
						std::cout << "DESTROYED" << std::endl;
					}
				}
			}
			break;
		}
	}

}