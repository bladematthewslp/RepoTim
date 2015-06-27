#pragma once


#include "Component.h"



class InputComponent : public Component
{
	protected:
		typedef unsigned int T_PressedKey;

		static const T_PressedKey s_KeyLeft = 0x01;
		static const T_PressedKey s_KeyUp = 0x02;
		static const T_PressedKey s_KeyRight = 0x04;
		static const T_PressedKey s_KeyDown = 0x08;
		static const T_PressedKey s_KeySpace = 0x10;
	public:
		InputComponent(GameObject& gameObject);
		virtual ~InputComponent();
		virtual void update(T_PressedKey pressedKey);
};