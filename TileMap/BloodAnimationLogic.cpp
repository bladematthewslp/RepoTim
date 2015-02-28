#include "BloodAnimationLogic.h"



BloodAnimationLogic::BloodAnimationLogic(GameObject* gameObject)
	: LogicComponent(gameObject)
{
	RenderComponent* render = gameObject->getRenderComponent();
	//render->mTexture.loadFromImage(RenderComponent::mImageHolder.get(Images::BloodAnimationA));
	//render->mTexture.setSmooth(true);
	
	render->mSprite.setTexture(&RenderComponent::mTextureHolder.get(Textures::BloodAnimationA));//render->mTexture);
	render->mSprite.setSize(sf::Vector2f(100,100));
	sf::IntRect bloodAnimation(512,0,512,512);
	render->createSpriteAnim(bloodAnimation,"BloodAnimation",true, 6,.6);
	render->setAnimation("BloodAnimation");
}

void BloodAnimationLogic::update(Grid& grid)
{
	mGameObject->mRenderComponent->runSpriteAnim(*mGameObject);
	if(mGameObject->mRenderComponent->getAnimStatus() == SpriteAnim::Status::SUCCESS)
	{
		System::removeGameObject(mGameObject);
	}
}