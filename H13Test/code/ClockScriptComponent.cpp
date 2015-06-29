#include "ClockScriptComponent.h"
#include "ClockColliderComponent.h"
#include "GameObject.h"
#include "Clock.h"
#include "time.h"



ClockScriptComponent::ClockScriptComponent(GameObject& gameObject)
	: ScriptComponent(gameObject)
	, mVelocity(-1.0f, 1.0f)
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
}


ClockScriptComponent::~ClockScriptComponent()
{
	if (hourHand)
		hourHand->Destroy();

	if (minuteHand)
		minuteHand->Destroy();

	if (secondHand)
		secondHand->Destroy();
}


void ClockScriptComponent::update()
{

	// move clock in random direction
	float screenWidth = mApplication->getScreenWidth();
	float screenHeight = mApplication->getScreenHeight();

	Vector2D pos = mGameObject.getPosition();

	mGameObject.move(mVelocity);



	if (!hourHand || !minuteHand)
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