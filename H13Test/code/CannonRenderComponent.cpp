#include "CannonRenderComponent.h"


CannonRenderComponent::CannonRenderComponent(GameObject& gameObject)
	: RenderComponent(gameObject)
{
	std::vector<Vector2D> verts =
	{
		Vector2D(0, -15),
		Vector2D(-10, +15),
		Vector2D(+10, +15),
	};

	setVertices(verts);

	std::vector<Color> colors =
	{
		GetRGB(255, 0, 0),
		GetRGB(0, 255, 0),
		GetRGB(0, 0, 255),
	};

	setColors(colors);
	

}
