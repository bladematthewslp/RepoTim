#include "RenderComponent.h"
#include "GameObject.h"
#include "Matrix.h"
#include "C_Application.h"
RenderComponent::RenderComponent(GameObject& gameObject)
	: Component(gameObject)
{

	mApplication->addComponent<RenderComponent>(this);
}

RenderComponent::~RenderComponent()
{

}

void RenderComponent::Draw()
{
	Vector2D pos = mGameObject.getPosition();
	float angle = mGameObject.getRotation();

	const int NUM_VERTICES = mVertices.size();
	std::vector<Vector2D> transformedVerts(NUM_VERTICES);
	Matrix2D op = Matrix2D::rotate(angle);

	for (unsigned int i = 0; i < NUM_VERTICES; i++)
	{
		transformedVerts[i] = op * mVertices[i];
	}

	for (unsigned int i = 0; i < NUM_VERTICES; i++)
	{
		DrawLine(pos.x + transformedVerts[i].x, pos.y + transformedVerts[i].y,
			pos.x + transformedVerts[(i + 1) % NUM_VERTICES].x, pos.y + transformedVerts[(i + 1) % NUM_VERTICES].y,
			mColors[i]);
	}


}


std::vector<Vector2D> RenderComponent::getVertices()
{
	return mVertices;
}