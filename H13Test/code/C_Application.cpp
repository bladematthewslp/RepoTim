#include "C_Application.h"
#include "graphics.h"
#include "time.h"
#include "Cannon.h"
#include "Clock.h"
#include "ClockScriptComponent.h"
std::vector<std::unique_ptr<GameObject>>	C_Application::mGameObjects;


C_Application::C_Application(int screenWidth, int screenHeight)
	: m_ScreenWidth(screenWidth)
	, m_ScreenHeight(screenHeight)
	, m_CannonX(m_ScreenWidth/2)
	, m_CannonY(m_ScreenHeight/1)
{
	
	Component::setApplication(this);
	GameObject::setApplicaton(this); 

	GameObject* cannon = GameObject::Create<Cannon>();
	cannon->setPosition(m_ScreenWidth / 2.0f, m_ScreenHeight / 1.10f);
	
	GameObject* clock =  GameObject::Create<Clock>();
	clock->setPosition(325, 127);
	dynamic_cast<ClockScriptComponent*>(clock->mScriptComponent)->setVelocity(Vector2D(-3.0f, 3.0f));

	GameObject* clock2 = GameObject::Create<Clock>();
	clock2->setPosition(127, 510);
	dynamic_cast<ClockScriptComponent*>(clock2->mScriptComponent)->setVelocity(Vector2D(+3.0f, -1.0f));


	
}


C_Application::~C_Application()
{
	while (mGameObjects.size() != 0)
	{
		(*mGameObjects.back()).removeAllComponentsAndGameObject();
	}
}


void C_Application::Tick(T_PressedKey pressedKeys)
{
	
	// Sample tick

	
	// Handle pending commands
	while (!mCommandQueue.empty())
	{
		mCommandQueue.front()();
		mCommandQueue.pop();
	}


	// update ColliderComponents
	for (auto collider = mColliderComponents.begin(); collider != mColliderComponents.end(); ++collider)
	{
		(*collider)->update();
	}
	
	for (int i = mColliderComponents.size() - 1; i >= 0; --i)// mColliderComponents.size(); i++)
	//for (auto collider = mColliderComponents.rbegin(); collider != mColliderComponents.rend(); ++collider)
	{ 
		mColliderComponents[i]->checkForCollision();
		//(*collider)->checkForCollision();
	}

	// Update input components
	for (auto input = mInputComponents.begin(); input != mInputComponents.end(); ++input)
	{
		(*input)->update(pressedKeys);
	}
	
	// Update script components
	for (auto script = mScriptComponents.begin(); script != mScriptComponents.end(); ++script)
	{
		(*script)->update();
	}

	// Clear entire screen
	FillRect(0, 0, m_ScreenWidth, m_ScreenHeight, GetRGB(0, 0, 0));

	// Draw all renderable game objects
	for (auto render = mRenderComponents.begin(); render != mRenderComponents.end(); ++render)
	{
		(*render)->Draw();
	}
}

void C_Application::addProjectile(GameObject* projectile)
{
	mProjectiles.push_back(projectile);
}

void C_Application::removeProjectile(GameObject* projectile)
{
	for (auto iter = mProjectiles.begin(); iter != mProjectiles.end(); ++iter)
	{
		if (*iter == projectile)
		{
			mProjectiles.erase(iter);
			break;
		}
	}
}

