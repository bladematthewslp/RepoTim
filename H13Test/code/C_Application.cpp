#include "C_Application.h"
#include "graphics.h"
#include "time.h"
#include "Cannon.h"
#include "Clock.h"

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
	clock->setPosition(200, 200);

	
	GameObject* clock2 = GameObject::Create<Clock>();
	clock2->setPosition(600, 400);


	
}


C_Application::~C_Application()
{

}


void C_Application::Tick(T_PressedKey pressedKeys)
{
	
	// Sample tick

	// Clear entire screen
	FillRect(0, 0, m_ScreenWidth, m_ScreenHeight, GetRGB(0, 0, 0));

	// Handle pending commands
	while (!mCommandQueue.empty())
	{
		mCommandQueue.front()();
		mCommandQueue.pop();
	}

	// Update input components
	int size = mInputComponents.size();
	for (int i = 0; i < size; i++)
	{
		mInputComponents[i]->update(pressedKeys);
	}
	
	
	// Update script components
	size = mScriptComponents.size();
	for (int i = 0; i < size; i++)
	{
		mScriptComponents[i]->update();
	}


	// Draw all renderable game objects
	size = mRenderComponents.size();
	for (int i = 0; i < size; i++)
	{
		mRenderComponents[i]->Draw();
	}
}