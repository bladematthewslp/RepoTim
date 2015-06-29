#include "ProjectileRenderComponent.h"
#include "GameObject.h"

ProjectileRenderComponent::ProjectileRenderComponent(GameObject& gameObject)
	: RenderComponent(gameObject)
{
	std::vector<Vector2D> verts =
	{
		Vector2D(-2, +10),
		Vector2D(-2, -10),
		Vector2D(+2, -10),
		Vector2D(+2, +10),
	};

	setVertices(verts);

	std::vector<Color> colors =
	{
		GetRGB(255, 0, 0),
		GetRGB(255, 0, 0),
		GetRGB(255, 0, 0),
		GetRGB(255, 0, 0),
	};

	setColors(colors);
}