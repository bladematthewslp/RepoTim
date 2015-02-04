#include "HealthBarLogic.h"

HealthBarLogic::HealthBarLogic(GameObject* gameObject)
	: LogicComponent(gameObject)
{


}

void HealthBarLogic::updateHealth(int num)
{
	switch(num)
	{
		case 100:
			mGameObject->getSprite()->setTexture( &mGameObject->mRenderComponent->mTextureHolder.get(Textures::HealthBar100));
			break;
		case 90:
			mGameObject->getSprite()->setTexture( &mGameObject->mRenderComponent->mTextureHolder.get(Textures::HealthBar90));
			break;
		case 80:
			mGameObject->getSprite()->setTexture( &mGameObject->mRenderComponent->mTextureHolder.get(Textures::HealthBar80));
			break;
		case 70:
			mGameObject->getSprite()->setTexture( &mGameObject->mRenderComponent->mTextureHolder.get(Textures::HealthBar70));
			break;
		case 60:
			mGameObject->getSprite()->setTexture( &mGameObject->mRenderComponent->mTextureHolder.get(Textures::HealthBar60));
			break;
		case 50:
			mGameObject->getSprite()->setTexture( &mGameObject->mRenderComponent->mTextureHolder.get(Textures::HealthBar50));
			break;
		case 40:
			mGameObject->getSprite()->setTexture( &mGameObject->mRenderComponent->mTextureHolder.get(Textures::HealthBar40));
			break;
		case 30:
			mGameObject->getSprite()->setTexture( &mGameObject->mRenderComponent->mTextureHolder.get(Textures::HealthBar30));
			break;
		case 20:
			mGameObject->getSprite()->setTexture( &mGameObject->mRenderComponent->mTextureHolder.get(Textures::HealthBar20));
			break;
		case 10:
			mGameObject->getSprite()->setTexture( &mGameObject->mRenderComponent->mTextureHolder.get(Textures::HealthBar10));
			break;
		case 0:
			mGameObject->getSprite()->setTexture( &mGameObject->mRenderComponent->mTextureHolder.get(Textures::HealthBar0));
			break;
		
	}

}