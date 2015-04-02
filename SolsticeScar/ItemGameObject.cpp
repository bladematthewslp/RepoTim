#include "ItemGameObject.h"
#include "RenderComponent.h"
#include "BoxColliderComponent.h"
#include "ItemLogic.h"
#include <iostream>

ItemGameObject::ItemGameObject(GameObjectDesc desc)
	: GameObject(desc)
{
	
	//mBoxColliderComponent->setVisible(true);

	mLogicComponent = std::unique_ptr<ItemLogic>(new ItemLogic(this)).release();
	
}

void ItemGameObject::setItemType(Item::Type item)
{
	switch(item)
	{
		case Item::RedOrb:
			this->mRenderComponent->mSprite.setTexture(&RenderComponent::mTextureHolder.get(Textures::RedOrb));
			//this->mRenderComponent->mImage = RenderComponent::mImageHolder.get(Images::RedOrb);
			break;
		case Item::GreenOrb:
			this->mRenderComponent->mSprite.setTexture(&RenderComponent::mTextureHolder.get(Textures::GreenOrb));
			//this->mRenderComponent->mImage = RenderComponent::mImageHolder.get(Images::GreenOrb);
			break;
		case Item::RyobeDagger:
			this->mRenderComponent->mSprite.setTexture(&RenderComponent::mTextureHolder.get(Textures::RyobeDagger));
			//this->mRenderComponent->mImage = RenderComponent::mImageHolder.get(Images::RyobeDagger);
			break;
	}
	//this->mRenderComponent->mTexture.loadFromImage(this->mRenderComponent->mImage);
	//this->mRenderComponent->mSprite.setTexture(&this->mRenderComponent->mTexture);

}