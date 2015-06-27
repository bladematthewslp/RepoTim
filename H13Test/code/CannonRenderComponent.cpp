#include "CannonRenderComponent.h"


CannonRenderComponent::CannonRenderComponent(GameObject& gameObject)
	: RenderComponent(gameObject)
{
	mVertices = 
	{
		Vector2D(0, -15),
		Vector2D(-10, +15),
		Vector2D(+10, +15),
	};

	mColors = 
	{
		GetRGB(255, 0, 0),
		GetRGB(0, 255, 0),
		GetRGB(0, 0, 255),
	};
	

}
