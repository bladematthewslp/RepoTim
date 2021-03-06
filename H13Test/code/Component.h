#pragma once


class GameObject;
class C_Application;

class Component
{
	friend class ClockColliderComponent;
	protected:
		GameObject& mGameObject;
		bool	mEnabled;
		
	public:
		Component(GameObject& gameObject);
		virtual ~Component();
		virtual void update();

		static C_Application* mApplication;
		static void setApplication(C_Application* app);
		GameObject& getGameObject() { return mGameObject;  }

		bool		getEnabled();
		void		setEnabled(bool flag);
};

