#include "SpriteAnim.h"
#include "GameObject.h"
#include <iostream>

SpriteAnim::SpriteAnim()
{

}
SpriteAnim::SpriteAnim(sf::IntRect rect, int numberFrames, int frameToHold, bool loop, float speed, int startFrame, int frameToAllowNextAttack) 
	: numFrames(numberFrames)
	, textureRect(rect)
	, currentFrame(startFrame)
	, startingFrame(startFrame)
	, deltaTime(sf::seconds(1.0f/60.0f))
	, deltaClock()
	, mFrameToHold(frameToHold)
	, mLoop(loop)
	, playSpeed(speed/16.5)
	, done(false)
	, mFrameToAllowNextAttack(frameToAllowNextAttack)
{ 
	//playSpeed = 1/16.5;//.5;
	slashDelaySpeed = playSpeed * 3.5;//1/9.25;
	oldPlaySpeed = playSpeed;
	timer = 0;
	timeSinceUpdate = sf::Time::Zero;
	
};
int SpriteAnim::run(GameObject& player)
{
	//if(done == true)
		//	return 0;
		
		timeSinceUpdate = deltaClock.restart();
		
		
			timer += deltaTime.asSeconds();

		if(timer >= playSpeed)
		{
			currentFrame++;

			if(currentFrame >= numFrames)
			{
				if(mLoop == true)
					currentFrame = startingFrame;
				else
				{	
					//done = true;
					return Status::SUCCESS;
				}
					//if(currentFrame == numFrames)
					{
						exit();
						return Status::SUCCESS;
					}
					//currentFrame--;

				
			}
			if(currentFrame == mFrameToHold)
			{
				//std::cout << "NOW " << mFrameToHold  << std::endl;
				playSpeed = slashDelaySpeed;
			}
			else
			{
				playSpeed = oldPlaySpeed;
			}
			timer = 0;
				
		}

		sf::IntRect newRect(currentFrame * textureRect.left, textureRect.top, textureRect.width, textureRect.height);
		
		player.getSprite()->setTextureRect(newRect);
		
		
		//if(timer == (playSpeed * numFrames) )
		//std::cout << timer << std::endl;
		
		

		return Status::RUNNING;
};
	
void SpriteAnim::exit()
{
	timer = 0;
	currentFrame = startingFrame;
	playSpeed = oldPlaySpeed;
	//timeSinceUpdate = sf::Time::Zero;
	//deltaClock.restart();
}

bool SpriteAnim::isAnimDelayed()
{
	return (playSpeed == slashDelaySpeed ? true : false );
}

int SpriteAnim::run(sf::RectangleShape& sprite)
{
	timeSinceUpdate = deltaClock.restart();
		
		
	timer += deltaTime.asSeconds();

	if(timer >= playSpeed)
	{
		currentFrame++;

		if(currentFrame >= numFrames)
		{
			if(mLoop == true)
				currentFrame = startingFrame;
			else
			{	
				//done = true;
				return Status::SUCCESS;
			}
				//if(currentFrame == numFrames)
				{
					exit();
					return Status::SUCCESS;
				}
				//currentFrame--;

				
		}
		if(currentFrame == mFrameToHold)
		{
			//std::cout << "NOW " << mFrameToHold  << std::endl;
			playSpeed = slashDelaySpeed;
		}
		else
		{
			playSpeed = oldPlaySpeed;
		}
		timer = 0;
				
	}

	sf::IntRect newRect(currentFrame * textureRect.left, textureRect.top, textureRect.width, textureRect.height);
	sprite.setTextureRect(newRect);
	//player.getSprite()->setTextureRect(newRect);
		
		
	//if(timer == (playSpeed * numFrames) )
	//std::cout << timer << std::endl;
		
		

	return Status::RUNNING;
};

bool SpriteAnim::allowNextAttack(int frameNum)
{
	if(mFrameToAllowNextAttack == -1 || frameNum < mFrameToAllowNextAttack)
		return false;
	else
		return true;

}