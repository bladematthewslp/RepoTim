#pragma once

#include <vector>
#include "Component.h"
#include "graphics.h"
#include "Vector.h"

class GameObject;

typedef unsigned int Color;

class RenderComponent : public Component
{
	
	
	protected:

		
		std::vector<Vector2D>	mTransformedVertices;
		std::vector<Color>		mColors;
		std::vector<Vector2D>	mVertices;

	private:
		
	public:	
		RenderComponent(GameObject& gameObject);
		virtual ~RenderComponent();
		virtual void Draw();
		
		void					scaleVertices(Vector2D scale);
		void					updateChildVertices(Vector2D scale);
		void					setVertices(std::vector<Vector2D>);
		std::vector<Vector2D>	getVertices();

		void					setColors(std::vector<Color> colors);
		std::vector<Color>		getColors();
};

