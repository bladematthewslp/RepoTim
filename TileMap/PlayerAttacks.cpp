#include "PlayerAttacks.h"
#include "Player.h"


PlayerAttack::PlayerAttack()
{

}
PlayerAttack::PlayerAttack(sf::IntRect rect, int numberFrames, int frameToHold) 
	: numFrames(numberFrames)
	, textureRect(rect)
	, currentFrame(0)
	, deltaTime(sf::seconds(1.0f/60.0f))
	, deltaClock()
{ 
	playSpeed = 1/12.5;
	slashDelaySpeed = 1/1.25;
	oldPlaySpeed = playSpeed;
	timer = 0;
	mFrameToHold = frameToHold;
	timeSinceUpdate = sf::Time::Zero;

};
int PlayerAttack::run(Player* player)
{
		timeSinceUpdate = deltaClock.restart();
		
		timer += deltaTime.asSeconds();
		
		//if(timer % playSpeed == 0)
		if(timer >= playSpeed)
		{
			currentFrame++;
			if(currentFrame >= numFrames)
			{
				//currentFrame = 0;
			}
			if(currentFrame == mFrameToHold)
			{
				std::cout << "NOW" << std::endl;
				playSpeed = slashDelaySpeed;
			}
			else
			{
				playSpeed = oldPlaySpeed;
			}
			timer = 0;
				
		}

		sf::IntRect newRect(currentFrame * textureRect.left, textureRect.top, textureRect.width, textureRect.height);
		
		player->setTextureRect(newRect);
		
		
		//if(timer == (playSpeed * numFrames) )
		//std::cout << timer << std::endl;
		if(currentFrame == numFrames)
		{
			exit();
			return Status::SUCCESS;
		}
		

		return Status::RUNNING;
};
	
void PlayerAttack::exit()
{
	timer = 0;
	currentFrame = 0;
	playSpeed = oldPlaySpeed;
	//timeSinceUpdate = sf::Time::Zero;
	//deltaClock.restart();
}