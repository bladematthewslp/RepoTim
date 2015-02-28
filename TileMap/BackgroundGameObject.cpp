#include "BackgroundGameObject.h"
#include "RenderComponent.h"


BackgroundGameObject::BackgroundGameObject(GameObjectDesc desc)
	: GameObject(desc)
{
	
	//mRenderComponent->mImage.loadFromFile("Sprites/forest_background.png");
	//mRenderComponent->mTexture = RenderComponent::mTextureHolder.get(Textures::WoodsBackground);//loadFromImage(mRenderComponent->mImage);
	mRenderComponent->mTexture.setRepeated(true);
	mRenderComponent->mSprite.setTexture(&RenderComponent::mTextureHolder.get(Textures::WoodsBackgroundComplete));

}