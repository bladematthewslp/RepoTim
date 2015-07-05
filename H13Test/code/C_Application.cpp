#include "C_Application.h"
#include "graphics.h"
#include "time.h"
#include "QuadTree.h"
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
	
	//mQuadTree = new QuadTree(0, mQuadTree->mColliderComponent);


	

	mProjectiles.reserve(50);
	mRenderComponents.reserve(50);
	mInputComponents.reserve(50);
	mScriptComponents.reserve(50);
	Component::setApplication(this);
	GameObject::setApplicaton(this); 

	//quad = Node::BuildQuadTree(Vector2D(400, 400), 400, 1);



	GameObject* cannon = GameObject::Create<Cannon>();
	cannon->setPosition(m_ScreenWidth / 2.0f, m_ScreenHeight / 1.10f);
	createTwoClocks();
	//GameObject* clock =  GameObject::Create<Clock>();
	//clock->scale(.20, .20);
	//clock->setPosition(300, 127);
	//dynamic_cast<ClockScriptComponent*>(clock->mScriptComponent)->setVelocity(Vector2D(-2.0f, 1.0f));

//	Object* obj = new Object(clock->mColliderComponent);
	//quad->InsertObject(quad, clock->mColliderComponent);

	
	/*
	clock = GameObject::Create<Clock>();
	clock->scale(.20, .20);
	clock->setPosition(54, 67);
	dynamic_cast<ClockScriptComponent*>(clock->mScriptComponent)->setVelocity(Vector2D(-2.0f, 1.0f));

	clock = GameObject::Create<Clock>();
	clock->scale(.20, .20);
	clock->setPosition(534, 87);
	dynamic_cast<ClockScriptComponent*>(clock->mScriptComponent)->setVelocity(Vector2D(-2.0f, 1.0f));

	clock = GameObject::Create<Clock>();
	clock->scale(.20, .20);
	clock->setPosition(382, 122);
	dynamic_cast<ClockScriptComponent*>(clock->mScriptComponent)->setVelocity(Vector2D(-2.0f, 1.0f));

	clock = GameObject::Create<Clock>();
	clock->scale(.20, .20);
	clock->setPosition(98, 444);
	dynamic_cast<ClockScriptComponent*>(clock->mScriptComponent)->setVelocity(Vector2D(-2.0f, 1.0f));

	clock = GameObject::Create<Clock>();
	clock->scale(.20, .20);
	clock->setPosition(404, 398);
	dynamic_cast<ClockScriptComponent*>(clock->mScriptComponent)->setVelocity(Vector2D(-2.0f, 1.0f));

	clock = GameObject::Create<Clock>();
	clock->scale(.20, .20);
	clock->setPosition(444, 444);
	dynamic_cast<ClockScriptComponent*>(clock->mScriptComponent)->setVelocity(Vector2D(-2.0f, 1.0f));

	clock = GameObject::Create<Clock>();
	clock->scale(.20, .20);
	clock->setPosition(544, 474);
	dynamic_cast<ClockScriptComponent*>(clock->mScriptComponent)->setVelocity(Vector2D(-2.0f, 1.0f));

	clock = GameObject::Create<Clock>();
	clock->scale(.20, .20);
	clock->setPosition(494, 494);
	dynamic_cast<ClockScriptComponent*>(clock->mScriptComponent)->setVelocity(Vector2D(-2.0f, 1.0f));

	clock = GameObject::Create<Clock>();
	clock->scale(.20, .20);
	clock->setPosition(600, 600);
	dynamic_cast<ClockScriptComponent*>(clock->mScriptComponent)->setVelocity(Vector2D(-2.0f, 1.0f));
	
	clock = GameObject::Create<Clock>();
	clock->scale(.20, .20);
	clock->setPosition(555, 555);
	dynamic_cast<ClockScriptComponent*>(clock->mScriptComponent)->setVelocity(Vector2D(-2.0f, 1.0f));

	//obj = new Object(clock->mColliderComponent);
	//quad->InsertObject(quad, clock->mColliderComponent);


	clock = GameObject::Create<Clock>();
	clock->scale(.20, .20);
	clock->setPosition(515, 551);
	dynamic_cast<ClockScriptComponent*>(clock->mScriptComponent)->setVelocity(Vector2D(-2.0f, 1.0f));

	//obj = new Object(clock->mColliderComponent);
	//quad->InsertObject(quad, clock->mColliderComponent);

	clock = GameObject::Create<Clock>();
	clock->scale(.20, .20);
	clock->setPosition(480, 515);
	dynamic_cast<ClockScriptComponent*>(clock->mScriptComponent)->setVelocity(Vector2D(-2.0f, 1.0f));

	//obj = new Object(clock->mColliderComponent);
	//quad->InsertObject(quad, clock->mColliderComponent);

	clock = GameObject::Create<Clock>();
	clock->scale(.20, .20);
	clock->setPosition(504, 344);
	dynamic_cast<ClockScriptComponent*>(clock->mScriptComponent)->setVelocity(Vector2D(-2.0f, 1.0f));

	//obj = new Object(clock->mColliderComponent);
	//quad->InsertObject(quad, clock->mColliderComponent);

	clock = GameObject::Create<Clock>();
	clock->scale(.20, .20);
	clock->setPosition(577, 150);
	dynamic_cast<ClockScriptComponent*>(clock->mScriptComponent)->setVelocity(Vector2D(-2.0f, 1.0f));

	//obj = new Object(clock->mColliderComponent);
	//quad->InsertObject(quad, clock->mColliderComponent);
	*/
	
	//dynamic_cast<ClockScriptComponent*>(clock2->mScriptComponent)->setVelocity(Vector2D(+1.0f, -2.5f));


	//obj = new Object(clock2->mColliderComponent);
	//quad->InsertObject(quad, clock2->mColliderComponent);

	

	//mQuadTree = new QuadTree(0, new AABB(0,screenWidth, 0, screenHeight));
	//ColliderComponent* main = new ColliderComponent(*mQuadTree);
	//main->setSize(0, 0, screenWidth, screenHeight);
	//mQuadTree->mBounds = main;
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
	if (Clock::NUM_CLOCKS == 0)
		createTwoClocks();
	
	// Handle pending commands
	while (!mCommandQueue.empty())
	{
		mCommandQueue.front()();
		mCommandQueue.pop();
	}
	/*
	mQuadTree->clear();

	for (int i = 0; i < mColliderComponents.size(); i++)
	{
		mQuadTree->insert(mColliderComponents[i]);
	}

	std::vector<ColliderComponent*> returnObjects;
	for (int i = 0; i < mColliderComponents.size(); i++)
	{
		returnObjects.clear();
		mQuadTree->retrieve(returnObjects, mColliderComponents[i]);
		int s = returnObjects.size();
		if (s > 0)
		{
			int ffd = 93;
		}
		for (int j = 0; j < returnObjects.size(); j++)
		{
			mColliderComponents[i]->checkForCollision(returnObjects[j]);// ->checkForCollision();
		}
   	}
	*/
	Node* newQuad = Node::BuildQuadTree(Vector2D(400, 300), 400, 1);
	for (int i = 0; i < mColliderComponents.size(); i++)
	{
		newQuad->InsertObject(newQuad, mColliderComponents[i]);
	}
	newQuad->TestAllCollisions(newQuad);

	int i = 0;
	// update ColliderComponents
	//for (auto collider = mColliderComponents.begin(); collider != mColliderComponents.end(); ++collider)
	{
	//	(*collider)->update();
	}
	
	
	//for (int i = mColliderComponents.size() - 1; i >= 0; --i)// mColliderComponents.size(); i++)
	//for (auto collider = mColliderComponents.rbegin(); collider != mColliderComponents.rend(); ++collider)
	{ 
		//mColliderComponents[i]->checkForCollision();
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

void C_Application::createTwoClocks()
{
	GameObject* clock = GameObject::Create<Clock>();
	clock->setPosition(300, 127);

	GameObject* clock2 = GameObject::Create<Clock>();
	clock2->setPosition(200, 400);
}

