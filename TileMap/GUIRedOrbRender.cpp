#include "GUIRedOrbRender.h"
#include "GUIRedOrbLogic.h"
#include <sstream>
#include <string>

std::string convertIntToString(int num)
{
	int number = num;       // number to be converted to a string
	std::string result;          // string which will contain the result
	std::ostringstream convert;   // stream used for the conversion
	convert << number;      // insert the textual representation of 'Number' in the characters in the stream
	result = convert.str(); // set 'Result' to the contents of the stream
	return result;
}


GUIRedOrbRender::GUIRedOrbRender(GameObject* gameObject)
	: RenderComponent(gameObject)
	, mTextColor(sf::Color(232,43,1,255))
{
	// load font
	mFont.loadFromFile("CHILLER.ttf");

	// initialize text
	mText.setFont(mFont);
	mText.setString("x0");
	mText.setPosition(875,50);
	mText.setColor(mTextColor);
	mText.setStyle(sf::Text::Bold);

	// initialize sprite
	//mTexture.loadFromImage(RenderComponent::mImageHolder.get(Images::RedOrb));
	mSprite.setSize(sf::Vector2f(27,45));
	mSprite.setTexture(&RenderComponent::mTextureHolder.get(Textures::RedOrb));//mTexture);
	mSprite.setPosition(100, 100);


	
}

void GUIRedOrbRender::update(sf::RenderTarget& window)
{
	int xOffset = window.getView().getCenter().x - window.getView().getSize().x/2;
	mText.setPosition(mGameObject->getPosition().x + xOffset + 10, mGameObject->getPosition().y + 10);
	mSprite.setPosition(mGameObject->getPosition().x + xOffset - 25, mGameObject->getPosition().y);
	
	//RenderComponent::update(window);
}

void GUIRedOrbRender::draw(sf::RenderTarget& window, sf::RenderStates states ) const
{
	window.draw(mText);
	window.draw(mSprite);
}

void GUIRedOrbRender::setRedOrbNum(int num)
{
	//mNumOrbs = num;
	std::string numOrbs = convertIntToString(num);
	mText.setString("x" + numOrbs);

}



void GUIRedOrbRender::fade()
{
	
	sf::Color color  = mText.getColor();
	if(color.a == 0)
		return;
	color.a -= 3;
	mText.setColor(color);

	color = mSprite.getFillColor();
	color.a -= 3;
	mSprite.setFillColor(color);
}

void GUIRedOrbRender::show()
{
	sf::Color color  = mText.getColor();
	color.a = 255;
	mText.setColor(color);

	color = mSprite.getFillColor();
	color.a = 255;
	mSprite.setFillColor(color);

}

