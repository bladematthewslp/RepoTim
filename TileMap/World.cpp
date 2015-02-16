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

#include <iostream>
World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(sf::FloatRect(0,0, 1024, 720))
	, mWorldBounds(0.0f, 0.0f, 1024.f, 720.f)
	, mWorldWidth(1024)
	, mWorldHeight(720)
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
	/*
	GameObjectDesc ryobeHUDHealthbarDesc("RyobeHUD", sf::RectangleShape(sf::Vector2f(352,20)), Layer::UI, ComponentType::RenderComponent);
	GameObject* ryobeHUDHealthbar = std::unique_ptr<GameObject>(new GameObject(ryobeHUDHealthbarDesc)).release();
	ryobeHUDHealthbar->setPosition(487, 679);
	ryobeHUDHealthbar->mRenderComponent->mSprite.setTexture(&ryobeHUDHealthbar->getRenderComponent()->mTextureHolder.get(Textures::RyobeHUDHealthbar));
	*/
	
	
	

	
	mGrid = std::unique_ptr<Grid>(new Grid()).release();

	// Add the background sprite to the scene
	GameObjectDesc backgroundDesc(	"Background", 
									sf::RectangleShape(sf::Vector2f(1024, 720)), 
									Layer::Background, 
									ComponentType::RenderComponent);

	
	for(int i = 0; i < 5; i++)
	{
		mBackground[i] = std::unique_ptr<GameObject>(new BackgroundGameObject(backgroundDesc)).release();
		mBackground[i]->setPosition( i * 1024, 0);
	}
	

	mPlayer = std::unique_ptr<GameObject>(new GameObject(GameObjectDesc("Player", sf::RectangleShape(), Layer::Player))).release();
	mPlayer->addComponent(ComponentType::RenderComponent, std::unique_ptr<Component>(new PlayerRender(mPlayer)).release());
	mPlayer->addComponent(ComponentType::LogicComponent, std::unique_ptr<Component>(new PlayerLogic(mPlayer)).release());// std::unique_ptr<Component>(new Player(&mPlayer)).release());
	mPlayer->addComponent(ComponentType::InputComponent, std::unique_ptr<Component>(new PlayerInput(mPlayer)).release());
	// Box Collider Component
	mPlayer->addComponent(ComponentType::BoxColliderComponent, std::unique_ptr<Component>(new PlayerBoxCollider(mPlayer)).release());
	mPlayer->mBoxColliderComponent->setSize(80, 98);
		//mPlayer->mBoxColliderComponent->setVisible(true);

	// block tests
	/*
	GameObjectDesc redBlockDesc("redBlock",sf::RectangleShape(sf::Vector2f(20,20)), Layer::Player, ComponentType::RenderComponent);//,ComponentType::LogicComponent);
	std::unique_ptr<GameObject> redBlock(new GameObject(redBlockDesc));
	redBlock->mRenderComponent->setFillColor(sf::Color::Red);	
	//redBlock->setChildPosition(200, -100);
	redBlock->setPosition(100, -50);
	std::cout << redBlock->getLocalPosition().x << "," << redBlock->getLocalPosition().y << std::endl;
	mPlayer->addChild(std::move(redBlock));
	
	block = System::findGameObjectByName("redBlock");
	std::cout << block->getLocalPosition().x << "," << block->getLocalPosition().y << std::endl;
	
	GameObjectDesc blueBlockDesc("blueBlock",sf::RectangleShape(sf::Vector2f(20,20)), Layer::Player, ComponentType::RenderComponent);//,ComponentType::LogicComponent);
	std::unique_ptr<GameObject> blueBlock(new GameObject(blueBlockDesc));
	blueBlock->mRenderComponent->setFillColor(sf::Color::Blue);	
	blueBlock->setPosition(100, 50);
	std::cout << blueBlock->getWorldPosition().x << "," << blueBlock->getWorldPosition().y << std::endl;
	
	block->addChild(std::move(blueBlock));
	GameObject* newBlock = System::findGameObjectByName("blueBlock");
	std::cout << newBlock->getWorldPosition().x << "," << newBlock->getWorldPosition().y << std::endl;
	std::cout << mPlayer->getWorldPosition().x << "," << mPlayer->getWorldPosition().y << std::endl;
	*/
	
	GameObjectDesc ninjaDesc("Ninja",sf::RectangleShape(), Layer::Enemy);//,ComponentType::LogicComponent);
	/*GameObject* ninja = std::unique_ptr<GameObject>(new NinjaGameObject(ninjaDesc)).release();
	ninja->setPosition(800,475);
	ninja->mBoxColliderComponent->setSize(50,75);
		*/
	//GameObjectDesc ninjaDesc("Ninja2",sf::RectangleShape(), Layer::Enemy);//,ComponentType::LogicComponent);
	
	
	GameObject* ninja2 = std::unique_ptr<GameObject>(new NinjaGameObject(ninjaDesc)).release();
	ninja2->setPosition(1200,475);
	ninja2->mBoxColliderComponent->setSize(50,75);
	
	GameObject* ninja3 = std::unique_ptr<GameObject>(new NinjaGameObject(ninjaDesc)).release();
	ninja3->setPosition(1500, 475);
	ninja3->mBoxColliderComponent->setSize(50,75);
	GameObject* ninja4 = std::unique_ptr<GameObject>(new NinjaGameObject(ninjaDesc)).release();
	ninja4->setPosition(2100, 475);
	ninja4->mBoxColliderComponent->setSize(50,75);
	GameObject* ninja5 = std::unique_ptr<GameObject>(new NinjaGameObject(ninjaDesc)).release();
	ninja5->setPosition(1800, 475);
	ninja5->mBoxColliderComponent->setSize(50,75);

	GameObjectDesc ryobeDesc("Ryobe",sf::RectangleShape(), Layer::Enemy);
	GameObject* ryobe = std::unique_ptr<GameObject>(new RyobeGameObject(ryobeDesc)).release();
	ryobe->setPosition(600, 568);
	
	/*
	//ryobe->Destroy();
	std::unique_ptr<GameObject> rr(new GameObject(redBlockDesc));
	rr->mRenderComponent->setFillColor(sf::Color::Red);
	//GameObject r(redBlockDesc);
	mPlayer->addChild(rr.get());
	*/
	//r.addComponent(ComponentType::LogicComponent);
	
	/*
	GameObjectDesc redBlockDesc("redBlock",sf::RectangleShape(sf::Vector2f(20,20)), Layer::Player, ComponentType::RenderComponent);//,ComponentType::LogicComponent);
	GameObject* rr = std::unique_ptr<GameObject>(new GameObject(redBlockDesc)).release();
	rr->mRenderComponent->setFillColor(sf::Color::Red);
	
	
	
	mPlayer->addChild(rr);
	
	GameObjectDesc blueBlockDesc("blueBlock",sf::RectangleShape(sf::Vector2f(20,20)), Layer::Player, ComponentType::RenderComponent);//,ComponentType::LogicComponent);
	GameObject* bb = std::unique_ptr<GameObject>(new GameObject(blueBlockDesc)).release();
	bb->mRenderComponent->setFillColor(sf::Color::Blue);
	bb->setPosition(50, -50);
	rr->addChild(bb);

	GameObjectDesc greenBlockDesc("greenBlock",sf::RectangleShape(sf::Vector2f(20,20)), Layer::Player, ComponentType::RenderComponent);//,ComponentType::LogicComponent);
	GameObject* gg = std::unique_ptr<GameObject>(new GameObject(greenBlockDesc)).release();
	gg->mRenderComponent->setFillColor(sf::Color::Green);
	gg->setPosition(-75, -100);
	bb->addChild(gg);
	*/
	
	mLookAtPoint = sf::Vector2f(mPlayer->getPosition().x, 360);
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
	if(dynamic_cast<PlayerLogic*>(mPlayer->mLogicComponent)->getDirection() == Direction::Right)
	{
		if(playerPosX > viewPosX + 50)
			mLookAtPoint.x += cameraLerpSpeed;
		//else if(playerPosX < viewPosX + 50)
			//mLookAtPoint.x -= cameraLerpSpeed;
	}
	else if(dynamic_cast<PlayerLogic*>(mPlayer->mLogicComponent)->getDirection() == Direction::Left)
	{
		if(playerPosX < viewPosX - 50)
			mLookAtPoint.x -= cameraLerpSpeed;
		//else if(playerPosX > viewPosX - 50)
			//mLookAtPoint.x += cameraLerpSpeed;
	}
	if(mLookAtPoint.x < worldViewXLimit)
	{
		mLookAtPoint.x = worldViewXLimit;
	}
	
	//mWorldView.setCenter(sf::Vector2f( (mPlayer->getPosition().x < 512 ? 512 : mPlayer->getPosition().x), 360));
	mWorldView.setCenter(mLookAtPoint);//sf::Vector2f( (mPlayer->getPosition().x < 512 ? 512 : mPlayer->getPosition().x), 360));
	mWindow.setView(mWorldView);
	System::draw(window);
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