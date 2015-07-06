#include "ClockScriptComponent.h"
#include "GameObject.h"
#include "Clock.h"
#include "time.h"
#include <random>

int getRandomNumber()
{
	 // Seed with a real random value, if available
	 std::random_device rd;

	 // Choose a random mean between 1 and 6
	 std::default_random_engine e1(rd());
	 std::uniform_int_distribution<int> uniform_dist(-3, 3);

	 int num = 0;

	 while (num == 0)
		 num = uniform_dist(e1);

	 return num;
}


ClockScriptComponent::ClockScriptComponent(GameObject& gameObject)
	: ScriptComponent(gameObject)
{
	hourHand = GameObject::Create<ClockHand>();
	minuteHand = GameObject::Create<ClockHand>();
	secondHand = GameObject::Create<ClockHand>();

	mGameObject.addChild(hourHand);
	mGameObject.addChild(minuteHand);
	mGameObject.addChild(secondHand);

	//mGameObject.scale(3.0f, 3.0f);
	hourHand->scale(.8f, .8f);
	secondHand->scale(.2f, 1.0f);

	mVelocity.x = (float)getRandomNumber();
	mVelocity.y = (float)getRandomNumber();
	
}


ClockScriptComponent::~ClockScriptComponent()
{
	
}


void ClockScriptComponent::update()
{

	// move clock 
	mGameObject.move(mVelocity);

	// bounce off walls
	AABB aabb = mGameObject.mColliderComponent->getCollider();
	if (aabb.xMin < 0)// || aabb.xMax > mApplication->getScreenWidth())
	{
		mGameObject.move(-aabb.xMin, 0);
		mVelocity.x *= -1;
	}
	else if (aabb.xMax > mApplication->getScreenWidth())
	{
		mGameObject.move( -(aabb.xMax - mApplication->getScreenWidth()), 0);
		mVelocity.x *= -1;
	}

	if (aabb.yMin < 0 )//|| aabb.yMax > mApplication->getScreenHeight())
	{
		mGameObject.move(0, -aabb.yMin);
		mVelocity.y *= -1;
	}
	else if (aabb.yMax > mApplication->getScreenHeight())
	{
		mGameObject.move(0, -(aabb.yMax - mApplication->getScreenHeight()));
		mVelocity.y *= -1;
	}
	
	// move hands
	if (!hourHand || !minuteHand || !secondHand)
		return;

	// get updated time
	int hr, min, sec = 0;

	GetTime(hr, min, sec);


	//rotate hour hand perperly
	float hour = ((k_PI / 6) * hr);
	float hrPercnt = (k_PI / 6) * ((float)min / 60);
	hourHand->setRotation(hour + hrPercnt);

	// rotate minute hand
	float minuteHandRotation = (k_PI / 30) * min;
	minuteHand->setRotation(minuteHandRotation);

	// rotate second hand
	float secondHandRotation = (k_PI / 30) * sec;
	secondHand->setRotation(secondHandRotation);


	

};


Vector2D ClockScriptComponent::getVelocity()
{
	return mVelocity;
}
void ClockScriptComponent::setVelocity(Vector2D vel)
{
	mVelocity = vel;
}