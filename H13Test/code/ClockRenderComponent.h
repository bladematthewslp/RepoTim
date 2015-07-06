#pragma once

#include "RenderComponent.h"

class ClockRenderComponent :public RenderComponent
{
	public:
		ClockRenderComponent(GameObject& gameObject);
		
		virtual ~ClockRenderComponent();

};



class ClockHandRenderComponent : public RenderComponent
{

public:
	ClockHandRenderComponent(GameObject& gameObject);
};

