#pragma once


#include "SFML/Graphics.hpp"
#include "Component.h"
#include "SpriteAnim.h"
#include "AttackType.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include <cassert>
#include <map>
class Component;
class GameObject;
class RenderComponent : public Component, public sf::Drawable
{
private:
	bool				mAnimStatus;
	
public:
	RenderComponent(GameObject* gameObject);
	~RenderComponent();
	static void			loadImages();

	static ImageHolder	mImageHolder;
	static TextureHolder mTextureHolder;

	sf::Image			mImage;
	sf::Texture			mTexture;
	sf::RectangleShape  mSprite;
	
	std::string			currentAnim;
	std::map<std::string, SpriteAnim*>	mSpriteSet;
	void				createSpriteAnim(sf::IntRect rect, std::string animName, bool loop, int numFrames,float speed = 1, int frameToHold = -1, int startingFrame = 0);
	int					runSpriteAnim(GameObject& gameObject);
	bool				getAnimStatus();
	void				stopSpriteAnim();
	void				setAnimation(std::string animName);
	void				setFillColor(sf::Color color);
	bool				isAnimDelayed();
	

	void				Awake();
	void				Destroy();
	void				FixedUpdate();
	void				LateUpdate();
	void				Start();
	virtual void		update(sf::RenderTarget& window);
	void				draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default ) const;
	void				render(sf::RenderWindow& window);
};
