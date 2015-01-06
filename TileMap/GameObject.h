#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Component.h"
#include <ObjBase.h>
#include <Guiddef.h>


class Component;
class RenderComponent;
class LogicComponent;
class InputComponent;
class BoxColliderComponent;
class PlayerState;
namespace ComponentType
{
	enum type
	{
		None				= 0,
		TransformComponent	= 1 << 0,
		RenderComponent		= 1 << 1,
		LogicComponent		= 1 << 2,
		InputComponent		= 1 << 3,
		AudioComponent		= 1 << 4,
		BoxColliderComponent= 1 << 5,

	};
}

#ifndef LAYER_
#define	LAYER_
namespace Layer
{
	typedef std::string Name;

	static std::string Background	= "Background",
				Default		= "Default",
				Enemy		= "Enemy",
				Foreground	= "Foreground",
				Layer		= "Layer",
				Player		= "Player",
				Root		= "Root",
				UI			= "UI";

	
	/*enum Name
	{
		Background,
		Default,
		Enemy,
		Foreground,
		Layer,
		Player,
		Root,
		UI
	};*/


}
#endif


struct GameObjectDesc
{
	
	GameObjectDesc(	const std::string& name = "GameObject", 
					sf::RectangleShape sprite = sf::RectangleShape(),
					Layer::Name layerName = Layer::Default, 
					int componentType = ComponentType::None,
					Component* componentScript = nullptr) 
						: mName(name), mSprite(sprite), mLayerName(layerName), mComponentType(componentType), mComponentScript(componentScript){};

	std::string			mName;
	sf::RectangleShape	mSprite;
	Layer::Name			mLayerName;
	int mComponentType;
	Component*			mComponentScript;
	
	

};

class GameObject : public sf::Transformable, private sf::Transform
{
	typedef std::vector<Component*> component_vector;
	typedef component_vector::iterator component_vector_itr;
	typedef component_vector::const_iterator  component_vector_const_itr;

	typedef std::vector<GameObject*> gameObject_vector;
	typedef gameObject_vector::iterator gameObject_vector_itr;
	typedef gameObject_vector::const_iterator  gameObject_vector_const_itr;

	

	
	

public:
	GUID						mID;
	std::string					mName;
	GameObject*					mParent;
	Layer::Name					mLayerName;
	PlayerState*				mState;
	std::vector<Component*>		mComponents;
	std::vector<GameObject*>	mChildren;

	//GameObject(sf::RectangleShape shape, int components, const std::string name = "GameObject");
	//GameObject(const std::string name = "GameObject");
	GameObject(GameObjectDesc desc);
	//~GameObject();

	LogicComponent*				mLogicComponent;
	RenderComponent*			mRenderComponent;
	InputComponent*				mInputComponent;
	BoxColliderComponent*		mBoxColliderComponent;
	void						addComponent(ComponentType::type, Component* = nullptr);
	RenderComponent*			getRenderComponent();
	sf::RectangleShape*				getSprite();
	
	
	
	void						addChild(GameObject* child);
	void						addComponent(Component* lComponent);
	
	
	std::vector<GameObject*>	findAllChildrenByName(std::string lName);
	GameObject*					findChildByName(std::string lName);
	Component*					findComponentByName(std::string lName);

	virtual void				create();
	virtual void				Awake();
	virtual void				Destroy();
	virtual void				FixedUpdate();
	virtual void				LateUpdate();
	virtual void				Start();
	virtual void				Update();

	void						constructComponents(GameObjectDesc& desc);
	void						updateTransforms();
	sf::Transform				getLocalTransform();
	sf::Transform				getWorldTransform();
	sf::Vector2f				getLocalPosition();
	sf::Vector2f				getWorldPosition();

	void						drawSceneGraph(sf::RenderWindow& window);






	template <typename T>
	T* findComponentByType()
	{
		
		for(component_vector_itr itr = mComponents.begin(); itr != mComponents.end(), ++itr)
		{
			if(T* lType == dynamic_cast<T*>(*itr))
				return lType;
		} 
		return nullptr;
	}


	







};

struct GameObjectComparer
{
	std::string mName;

	GameObjectComparer(std::string name)
		: mName(name)
	{


	}

	bool operator() (GameObject* lObject)
	{
		return (lObject->mName == mName? true : false);
	}

};