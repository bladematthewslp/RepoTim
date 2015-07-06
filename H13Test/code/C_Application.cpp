#include "C_Application.h"
#include "QuadTree.h"
#include "Cannon.h"
#include "Clock.h"
#include <random>

std::vector<std::unique_ptr<GameObject>>	C_Application::mGameObjects;



C_Application::C_Application(int screenWidth, int screenHeight)
	: m_ScreenWidth(screenWidth)
	, m_ScreenHeight(screenHeight)
	, m_CannonX(m_ScreenWidth/2)
	, m_CannonY(m_ScreenHeight/1)
{
	mProjectiles.reserve(50);
	mRenderComponents.reserve(50);
	mInputComponents.reserve(50);
	mScriptComponents.reserve(50);

	Component::setApplication(this);
	GameObject::setApplicaton(this); 

	// create cannon
	GameObject* cannon = GameObject::Create<Cannon>();
	cannon->setPosition(m_ScreenWidth / 2.0f, m_ScreenHeight / 1.10f);

	// create two clocks to start with
	createTwoClocks();
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
	
	

	// Build quadtree, adding all current colliders to it appropriately
	Node* newQuad = Node::BuildQuadTree(Vector2D(m_ScreenWidth, m_ScreenHeight), m_ScreenWidth, 1);
	for (int i = 0; i < mColliderComponents.size(); i++)
	{
		newQuad->InsertObject(newQuad, mColliderComponents[i]);
	}
	// test all collisions and handle appropriately
	newQuad->TestAllCollisions(newQuad);

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

void C_Application::createTwoClocks()
{
	// Seed with a real random value, if available
	std::random_device rd;

	// Choose a random mean between 1 and 6
	std::default_random_engine e1(rd());
	std::uniform_int_distribution<int> uniform_distX(0, m_ScreenWidth / 4);
	std::uniform_int_distribution<int> uniform_distY(0, m_ScreenHeight);
	
	int randX = uniform_distX(e1);
	int randY = uniform_distY(e1);
	
	// create one clock with random position
	GameObject* clock = GameObject::Create<Clock>();
	clock->setPosition(randX, randY);

	// reset random parameters
	uniform_distX = std::uniform_int_distribution<int>(m_ScreenWidth * 0.6, m_ScreenWidth);
	uniform_distY.reset();
	randX = uniform_distX(e1);
	randY = uniform_distY(e1);

	// create second clock with new random position
	GameObject* clock2 = GameObject::Create<Clock>();
	clock2->setPosition(randX, randY);
}



C_Application::~C_Application()
{
	while (mGameObjects.size() != 0)
	{
		(*mGameObjects.back()).removeAllComponentsAndGameObject();
	}
}