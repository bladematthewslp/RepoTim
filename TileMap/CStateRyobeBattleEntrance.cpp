#include "CStateRyobeBattleEntrance.h"
#include "CStateRyobeStanding.h"
#include "RyobeLogic.h"

CStateRyobeBattleEntrance::CStateRyobeBattleEntrance(GameObject* character)
	: CState("CStateRyobeBattleEntrance")
{
	character->mRenderComponent->setAnimation("TeleportIn");
	timerToBeginBattle = 0.0f;

	// create Ryobe HUD
	GameObjectDesc ryobeHUDDesc("RyobeHUD", sf::RectangleShape(sf::Vector2f(607,160)), Layer::UI, ComponentType::RenderComponent);
	ryobeHUD = std::unique_ptr<GameObject>(new GameObject(ryobeHUDDesc)).release();
	ryobeHUD->setPosition(400, 578);
	ryobeHUD->mRenderComponent->mSprite.setTexture(&ryobeHUD->getRenderComponent()->mTextureHolder.get(Textures::RyobeHUD));
	sf::Color color = ryobeHUD->getSprite()->getFillColor();
	color.a = 0;
	ryobeHUD->getSprite()->setFillColor(color);

	mHealthBarWidth = 352;
	mHealthBarHeight = 20;
	mMaxBarWidth = mHealthBarWidth;
	GameObjectDesc healthBarDesc("RyobeHealthBar",sf::RectangleShape(sf::Vector2f(mHealthBarWidth,mHealthBarHeight)), Layer::UI, ComponentType::RenderComponent);
	mHealthBar = std::unique_ptr<GameObject>(new GameObject(healthBarDesc)).release();
	mHealthBar->mRenderComponent->mTexture = mHealthBar->getRenderComponent()->mTextureHolder.get(Textures::RyobeHUDHealthbar);
	mHealthBar->mRenderComponent->mSprite.setTexture(&mHealthBar->mRenderComponent->mTexture);
	mMaxRectWidth = mHealthBar->mRenderComponent->mSprite.getTextureRect().width;
	mHealthBar->setPosition(487, 677);

	color = mHealthBar->getSprite()->getFillColor();
	color.a = 0;
	mHealthBar->getSprite()->setFillColor(color);

}


CState* CStateRyobeBattleEntrance::update(GameObject* character, sf::Time dt, Grid& grid)
{
	if( character->mRenderComponent->runSpriteAnim(*character) == SpriteAnim::Status::SUCCESS)
	{
		
		timerToBeginBattle += dt.asSeconds();

		sf::Color color = ryobeHUD->getSprite()->getFillColor();
		if(color.a < 250)
			color.a += 5;
		else 
			color.a = 255;
		ryobeHUD->getSprite()->setFillColor(color);
		
		color = mHealthBar->getSprite()->getFillColor();
		if(color.a < 250)
			color.a += 5;
		else 
			color.a = 255;
		mHealthBar->getSprite()->setFillColor(color);
		if(timerToBeginBattle >= 3)
		{
			
			RyobeLogic* ryobeLogic = dynamic_cast<RyobeLogic*>(character->mLogicComponent);
			ryobeLogic->setHealthBar(this->mHealthBar);
			
			CState* newState = std::unique_ptr<CState>(new CStateRyobeStanding(character)).release();
			newState->entry(character);
			return newState;
		}
	}
	
	return this;
}