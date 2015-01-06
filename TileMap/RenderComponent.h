#pragma once


#include "SFML/Graphics.hpp"
#include "Component.h"
#include "SpriteAnim.h"
#include <map>
class Component;
class GameObject;
class RenderComponent : public Component, public sf::Drawable
{
	
public:
	RenderComponent(GameObject* parent);
	sf::Image			mImage;
	sf::Texture			mTexture;
	sf::RectangleShape  mSprite;
	
	std::string			currentAnim;
	std::map<std::string, SpriteAnim*>	mSpriteSet;
	void				createSpriteAnim(sf::IntRect rect, std::string animName, bool loop, int numFrames,float speed = 1, int frameToHold = -1, int startingFrame = 0);
	int				runSpriteAnim(GameObject& gameObject);
	void				stopSpriteAnim();
	void				setAnimation(std::string animName);
	void				setFillColor(sf::Color color);
	bool				isAnimDelayed();
	

	void	Awake();
	void	Destroy();
	void	FixedUpdate();
	void	LateUpdate();
	void	Start();
	virtual void	update();
	void	draw(sf::RenderTarget& target, sf::RenderStates states ) const;
	void	render(sf::RenderWindow& window);
};