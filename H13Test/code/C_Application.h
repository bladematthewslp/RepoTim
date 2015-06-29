#ifndef TEST_C_APPLICATION_H
#define TEST_C_APPLICATION_H

#include <vector>
#include <memory>
#include <functional>
#include <queue>
#include "GameObject.h"

class C_Application
{
	friend class GameObject;
	friend class Component;
public:

	typedef unsigned int T_PressedKey;
	typedef std::vector<std::unique_ptr<GameObject>>::iterator GameObjectsIter;

	C_Application(int screenWidth, int screenHeight);
	~C_Application();

	/// Tick is called on fix framerate (50fps)
	void Tick(T_PressedKey pressedKeys);

	static const T_PressedKey s_KeyLeft  = 0x01;
	static const T_PressedKey s_KeyUp    = 0x02;
	static const T_PressedKey s_KeyRight = 0x04;
	static const T_PressedKey s_KeyDown  = 0x08;
	static const T_PressedKey s_KeySpace = 0x10;

	// Added by Timothy Matthews;
	//std::unique_ptr<GameObject>* createGameObject(std::string name = "GameObject");
	const int getScreenWidth() const { 	return m_ScreenWidth;}

	const int getScreenHeight() const {	return m_ScreenHeight;}

	void											addProjectile(GameObject* projectile);
	void											removeProjectile(GameObject* projectile);
	std::vector<GameObject*>&						getProjectiles() { return mProjectiles;  }


	template <typename T>
	void addComponent(Component* component);

	std::queue < std::function<void()>> mCommandQueue;
	std::vector<ColliderComponent*>					mColliderComponents;
	
private:

	const int	m_ScreenWidth;
	const int	m_ScreenHeight;
	
	// Members for sample tick
	int			m_CannonX;
	int			m_CannonY;
	
	// Added by Timothy Matthews
	static std::vector<std::unique_ptr<GameObject>>	mGameObjects;
	std::vector<GameObject*>						mProjectiles;
	std::vector<RenderComponent*>					mRenderComponents;
	std::vector<InputComponent*>					mInputComponents;
	std::vector<ScriptComponent*>					mScriptComponents;
	
	

};

template <typename T>
void C_Application::addComponent(Component* component)
{
	if (dynamic_cast<RenderComponent*>(component) != nullptr)
		mRenderComponents.push_back(dynamic_cast<RenderComponent*>(component));
	else if (dynamic_cast<InputComponent*>(component) != nullptr)
		mInputComponents.push_back(dynamic_cast<InputComponent*>(component));
	else if (dynamic_cast<ScriptComponent*>(component) != nullptr)
		mScriptComponents.push_back(dynamic_cast<ScriptComponent*>(component));
	else if (dynamic_cast<ColliderComponent*>(component) != nullptr)
		mColliderComponents.push_back(dynamic_cast<ColliderComponent*>(component));
	
}







#endif // #ifndef TEST_C_APPLICATION_H
