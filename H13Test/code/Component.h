#pragma once


class GameObject;
class C_Application;
class Component
{
	protected:
		GameObject& mGameObject;
		
	public:
		Component(GameObject& gameObject);
		virtual ~Component();
		virtual void update();

		static C_Application* mApplication;
		static void setApplication(C_Application* app);
};

