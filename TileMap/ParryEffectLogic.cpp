#include "ParryEffectLogic.h"
#include "RenderComponent.h"
#include "CState.h"

ParryEffectLogic::ParryEffectLogic(GameObject* gameObject)
	: LogicComponent(gameObject)
{
	RenderComponent* render = gameObject->getRenderComponent();
	render->mTexture.loadFromImage(RenderComponent::mImageHolder.get(Images::Parry));
	render->mSprite.setTexture(&render->mTexture);
	

	gameObject->mRenderComponent->createSpriteAnim(sf::IntRect(512,0,512,512),"Parry", true, 7, 1);
	gameObject->mRenderComponent->setAnimation("Parry");
}

void ParryEffectLogic::update(Grid& grid)
{
	mGameObject->mRenderComponent->runSpriteAnim(*mGameObject);

	if(ryobeGameObject->mState->getName() != "CStateRyobeAttacking")
		System::removeGameObject(mGameObject);
	
}