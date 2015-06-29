#include "ClockRenderComponent.h"


ClockRenderComponent::ClockRenderComponent(GameObject& gameObject)
	: RenderComponent(gameObject)
{
	std::vector<Vector2D> verts =
	{
		Vector2D(-50, +50),
		Vector2D(-50, -50),
		Vector2D(+50, -50),
		Vector2D(+50, +50),
	};

	setVertices(verts);

	std::vector<Color> colors =
	{
		GetRGB(255, 255, 255),
		GetRGB(255, 255, 255),
		GetRGB(255, 255, 255),
		GetRGB(255, 255, 255),

	};

	setColors(colors);
}




ClockRenderComponent::~ClockRenderComponent()
{
}





ClockHandRenderComponent::ClockHandRenderComponent(GameObject& gameObject)
	: RenderComponent(gameObject)
{
	std::vector<Vector2D> verts =
	{
		Vector2D(-2, 0),
		Vector2D(-2, -20),
		Vector2D(0, -50),
		Vector2D(2, -20),
		Vector2D(2, 0),
	};
	setVertices(verts);

	std::vector<Color> colors =
	{
		GetRGB(255, 255, 255),
		GetRGB(255, 255, 255),
		GetRGB(255, 255, 255),
		GetRGB(255, 255, 255),
		GetRGB(255, 255, 255),
	};

	setColors(colors);
}
