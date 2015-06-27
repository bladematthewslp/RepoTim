#include "Clock.h"
#include "time.h"

Clock::Clock(std::string name)
	: GameObject(name)
{
	mRenderComponent = new ClockRenderComponent(*this);
	mScriptComponent = new ClockScriptComponent(*this);
};

ClockHand::ClockHand(std::string name)
	: GameObject(name)
{
	mRenderComponent = new ClockHandRenderComponent(*this);
}

ClockRenderComponent::ClockRenderComponent(GameObject& gameObject)
	: RenderComponent(gameObject)
{
	mVertices =
	{
		Vector2D(-50, +50),
		Vector2D(-50, -50),
		Vector2D(+50, -50),
		Vector2D(+50, +50),
	};

	mColors =
	{
		GetRGB(255, 255, 255),
		GetRGB(255, 255, 255),
		GetRGB(255, 255, 255),
		GetRGB(255, 255, 255),

	};
}



ClockScriptComponent::ClockScriptComponent(GameObject& gameObject)
	: ScriptComponent(gameObject)
	, mVelocity(3.0f, 3.0f)
{
	hourHand = GameObject::Create<ClockHand>();
	minuteHand = GameObject::Create<ClockHand>();
	secondHand = GameObject::Create<ClockHand>();
	
	
	//hourHand->setScale(0.7f, 0.7f);
	//secondHand->setScale(.2f, 1.0f);

	mGameObject.addChild(hourHand);
	mGameObject.addChild(minuteHand);
	mGameObject.addChild(secondHand);

	mGameObject.setScale(3, 3);
	hourHand->setScale(3,2.1f);
	secondHand->setScale(.2f, 3.0f);
	
}
void ClockScriptComponent::update()
{
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


	// move clock in random direction
	float screenWidth = mApplication->getScreenWidth();
	float screenHeight = mApplication->getScreenHeight();
	Vector2D pos = mGameObject.getPosition();
	pos.x += mVelocity.x;
	if (pos.x < 0 || pos.x > screenWidth)
	{
		mVelocity.x *= -1;
		pos.x += mVelocity.x;
	}

	pos.y += mVelocity.y;
	if (pos.y < 0 || pos.y > screenHeight)
	{
		mVelocity.y *= -1;
		pos.y += mVelocity.y;
	}

	mGameObject.setPosition(pos);

};

ClockScriptComponent::~ClockScriptComponent()
{
	if (hourHand)
		hourHand->Destroy();

	if (minuteHand)
		minuteHand->Destroy();

	if (secondHand)
		secondHand->Destroy();
}



ClockHandRenderComponent::ClockHandRenderComponent(GameObject& gameObject)
	: RenderComponent(gameObject)
{
	mVertices =
	{
		Vector2D(-2, 0),
		Vector2D(-2, -20),
		Vector2D(0, -50),
		Vector2D(2, -20),
		Vector2D(2, 0),
	};

	mColors =
	{
		GetRGB(255, 255, 255),
		GetRGB(255, 255, 255),
		GetRGB(255, 255, 255),
		GetRGB(255, 255, 255),
		GetRGB(255, 255, 255),
	};
}

