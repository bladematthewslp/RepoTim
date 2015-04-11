#include "World.h"


#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "RenderComponent.h"

#include "ItemGameObject.h"
#include "NinjaLogic.h"

#include "BattleReadyState.h"
#include "CStateRyobeBattleEntrance.h"
#include "WinState.h"

#include <iostream>
World::World(Scene::Context& context)
	: mContext(&context)
	, mWindow(*context.window)
	, mWorldView(sf::FloatRect(0,0, 1024, 720))
	, mWorldBounds(0.0f, 0.0f, 5080.0f, 720.f)
	, mWorldWidth(1024)
	, mWorldHeight(720)
	, mFadeOutShape(sf::Vector2f(2000,2000))
{
	/*
	// init stuff here
	SoundPlayer::loadAllSounds();
	RenderComponent::loadImages();
	System::init(*this);
	Attacks::registerAttacks();

	std::cout << "Context address = " << &context << std::endl;

	init();*/
}

void World::init()
{
	
}

bool World::handleEvent(sf::RenderWindow& window, sf::Event& event)
{
	System::handleEvent(window, event);
	return true;
	/*
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
		//std::cout << (int)(pos.x + mWorldView.getCenter().x - 512)/32 << "," << pos.y/32 << std::endl;
	}
	return true;
	*/
}

bool World::handleInput(sf::Event& event)
{
	
	System::handleInput(event);
	return true;
	
}

/*
unsigned int World::update(sf::Time dt)
{
	
}
*/

void World::draw(sf::RenderWindow& window)
{
	

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
						//std::cout << "DESTROYED" << std::endl;
						break;
					}
				}
			}
			//break;
		}
		if((*layer_itr)->mName == Layer::Default)
		{
			std::vector<GameObject*>::iterator obj_itr;
			for(obj_itr = (*layer_itr)->mChildren.begin(); obj_itr != (*layer_itr)->mChildren.end(); obj_itr++)
			{
				if((*obj_itr)->mName == "GreenOrb" || (*obj_itr)->mName == "RedOrb" )
				{
					float dist = std::abs(mWorldView.getCenter().y - (*obj_itr)->getWorldPosition().y);
					if(dist > mWorldView.getSize().y/2)
					{
						System::removeGameObject( (*obj_itr) );
						//std::cout << "DESTROYED" << std::endl;
						break;
					}
				}
			}
		}
	}

}

void World::fadeIn()
{
	sf::Time dt = sf::seconds(1.0/60.0);
	static float timer = 0;
	timer += dt.asSeconds() * 50;
	if(timer > 1)
	{
		// fade in
		sf::Color color = mFadeOutShape.getFillColor();
		if(color.a > 5)
		{
			color.a -= dt.asSeconds() * 50;
		}
		else
		{
			color.a = 0;
		}
		mFadeOutShape.setFillColor(color);
	
		timer = 0;
	}
}

void World::cleanupWorld()
{
	System::mMusicPlayer.stop();
	System::removeAllGameObjects();
	RenderComponent::unloadImages();
	SoundPlayer::mSoundBuffers.mResourceMap.clear();
}

void World::restartWorld()
{
	System::mMusicPlayer.stop();
	System::removeAllGameObjects();
	
	init();
}


void World::updateCamera()
{
	mWorldView.setCenter(mLookAtPoint);
}