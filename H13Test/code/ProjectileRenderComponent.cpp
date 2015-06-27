#include "ProjectileRenderComponent.h"
#include "GameObject.h"

ProjectileRenderComponent::ProjectileRenderComponent(GameObject& gameObject)
	: RenderComponent(gameObject)
{
	mVertices =
	{
		Vector2D(-2, +10),
		Vector2D(-2, -10),
		Vector2D(+2, -10),
		Vector2D(+2, +10),
	};

	mColors =
	{
		GetRGB(255, 0, 0),
		GetRGB(255, 0, 0),
		GetRGB(255, 0, 0),
		GetRGB(255, 0, 0),
	};
}