#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"
#include "System.h"


struct Grid;
class LogicComponent : public Component
{
public:
	//GameObject*		mParent;

	virtual int getDirection();
	LogicComponent(GameObject* gameObject);
	~LogicComponent();
	void	Awake();
	void	Destroy();
	void	FixedUpdate();
	void	LateUpdate();
	void	Start();
	virtual void	update(Grid& grid);


};