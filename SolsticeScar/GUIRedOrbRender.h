#pragma once


#include "RenderComponent.h"

class GUIRedOrbRender : public RenderComponent
{
	sf::Font		mFont;
	sf::Color		mTextColor;
public:
	sf::Text		mText;
	
	GUIRedOrbRender(GameObject* gameObject);
	void		update(sf::RenderTarget& window);
	void		draw(sf::RenderTarget& window, sf::RenderStates states ) const;
	void		fade();
	void		show();
	void		setRedOrbNum(int num);
	int			mNumOrbs;
};