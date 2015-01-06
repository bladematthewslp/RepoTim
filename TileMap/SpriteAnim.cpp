#include "SpriteAnim.h"
#include "GameObject.h"
#include <iostream>

SpriteAnim::SpriteAnim()
{

}
SpriteAnim::SpriteAnim(sf::IntRect rect, int numberFrames, int frameToHold, bool loop, float speed, int startFrame) 
	: numFrames(numberFrames)
	, textureRect(rect)
	, currentFrame(startFrame)
	, startingFrame(startFrame)
	, deltaTime(sf::seconds(1.0f/60.0f))
	, deltaClock()
	, mFrameToHold(frameToHold)
	, mLoop(loop)
	, playSpeed(speed/16.5)
{ 
	//playSpeed = 1/16.5;//.5;
	slashDelaySpeed = 1/9.25;
	oldPlaySpeed = playSpeed;
	timer = 0;
	timeSinceUpdate = sf::Time::Zero;
	
};
int SpriteAnim::run(GameObject& player)
{
		
		timeSinceUpdate = deltaClock.restart();
		
		timer += deltaTime.asSeconds();
		//std::cout << currentFrame << std::endl;
		//if(timer % playSpeed == 0)
		if(timer >= playSpeed)
		{
			currentFrame++;
			//std::cout << currentFrame << std::endl;
			if(currentFrame >= numFrames)
			{
				if(mLoop == true)
					currentFrame = startingFrame;
				else
				{	
					//if(currentFrame == numFrames)
					{
						exit();
						return Status::SUCCESS;
					}
					//currentFrame--;

				}
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