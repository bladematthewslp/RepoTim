#pragma once

#include <vector>
#include "Component.h"
#include "graphics.h"
#include "Vector.h"
class GameObject;

class RenderComponent : public Component
{
	typedef unsigned int Color;
	
	protected:

		std::vector<Vector2D>	mVertices;
		std::vector<Color>		mColors;
		

	private:

	public:	
		RenderComponent(GameObject& gameObject);
		virtual ~RenderComponent();
		virtual void Draw();
		
		std::vector<Vector2D>	getVertices();
		std::vector<Color>		getColors();
};

