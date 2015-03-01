#include "GUIRedOrbLogic.h"
#include "GUIRedOrbRender.h"

GUIRedOrbLogic::GUIRedOrbLogic(GameObject* gameObject)
	: LogicComponent(gameObject)
	, deltaTime(sf::seconds(1.0f/60.0f))
	, timerGUI(15)
{
	
	mGameObject->setPosition(900,20);
}

void	GUIRedOrbLogic::update(Grid& grid)
{
	
	if(timerGUI != 0)
	{
		timerGUI -= deltaTime.asSeconds();
		if(timerGUI < 3)
		{
			//std::cout << "LESS THAN 5" << std::endl;
			dynamic_cast<GUIRedOrbRender*>(mGameObject->mRenderComponent)->fade();
		}
		if(timerGUI <= 0)
		{
			timerGUI = 0;
			//std::cout << "timer is 0" << std::endl;
		}
	}
	//std::cout << timerGUI << std::endl;

}

void GUIRedOrbLogic::showRedOrbGUI()
{
	timerGUI = 9;
	dynamic_cast<GUIRedOrbRender*>(mGameObject->mRenderComponent)->show();
}