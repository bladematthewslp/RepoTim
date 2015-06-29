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

void RenderComponent::setVertices(std::vector<Vector2D> vertices)
{
	mVertices = vertices;
	mTransformedVertices = mVertices;
}

void RenderComponent::scaleVertices(Vector2D scale)
{
	int i = 0;
	for (auto verts = mTransformedVertices.begin(); verts != mTransformedVertices.end(); ++verts, ++i)
	{
		verts->x = mTransformedVertices[i].x * scale.x;
		verts->y = mTransformedVertices[i].y * scale.y;
	}
	
	updateChildVertices(scale);
	/*
	for (auto child = mGameObject.getChildren().begin(); child != mGameObject.getChildren().end(); ++child)
	{
		if ((*child)->mRenderComponent)
			(*child)->mRenderComponent->setScale(scale);// Vector2D(scale.x / (*child)->getScale().x, scale.y / (*child)->getScale().y));
	}
	*/
	
}

void RenderComponent::updateChildVertices(Vector2D scale)
{
	for (auto child = mGameObject.getChildren().begin(); child != mGameObject.getChildren().end(); ++child)
	{
		if ((*child)->mRenderComponent)
		{
			int i = 0;
			for (auto verts = (*child)->mRenderComponent->mTransformedVertices.begin(); verts != (*child)->mRenderComponent->mTransformedVertices.end(); ++verts, ++i)
			{
				verts->x = (*child)->mRenderComponent->mTransformedVertices[i].x * scale.x;
				verts->y = (*child)->mRenderComponent->mTransformedVertices[i].y * scale.y;
			}
			(*child)->mRenderComponent->updateChildVertices(scale);
		}
			//(*child)->mRenderComponent->setScale(scale);// Vector2D(scale.x / (*child)->getScale().x, scale.y / (*child)->getScale().y));
	}
}

void RenderComponent::setColors(std::vector<Color> colors)
{
	mColors = colors;
}

void RenderComponent::Draw()
{
	Vector2D pos = mGameObject.getPosition();
	float angle = mGameObject.getRotation();
	
	const int NUM_VERTICES = mTransformedVertices.size();
	std::vector<Vector2D> transformedVerts(NUM_VERTICES);
	Matrix2D op = Matrix2D::rotate(angle);

	for (unsigned int i = 0; i < NUM_VERTICES; i++)
	{
		transformedVerts[i] = op * mTransformedVertices[i];
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
	return mTransformedVertices;
}