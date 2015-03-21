void PlayerLogic::update(Grid& grid)
{
	// this is unorthodox but it needs to be here to update every frame
	PlayerInput* input = dynamic_cast<PlayerInput*>(mGameObject->mInputComponent);
	input->handleKeyQueue();

	if(mVelocity.y != 0)// && (mGameObject->mState->getName() != "JumpingState" || mGameObject->mState->getName() != "FallingState") )
		mIsGrounded = false;
	else
		mIsGrounded = true;

	
	
	CState* state = mGameObject->mState->update(playerObject, deltaTime, grid);
	if(state != mGameObject->mState)
	{
		mGameObject->mState = state;
	}

	
}



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
	int					mComponentType;
	Component*			mComponentScript;
	
	

};

class GameObject : public sf::Transformable, private sf::Transform
{
	private:
		// Game Object Components
		LogicComponent*				mLogicComponent;
		RenderComponent*			mRenderComponent;
		InputComponent*				mInputComponent;
		BoxColliderComponent*		mBoxColliderComponent;
		
		// Game Object properties 
		GUID						mID;			// unique global identifier
		std::string					mName;			// game object name
		GameObject*					mParent;		// point to parent object
		Layer::Name					mLayerName;		// name of layer for rendering and collision detection
		CState*						mState;			// 
	
		std::vector<GameObject*>	mChildren;		// vector of children game objects

		static int GameObjectCounter = 0;

	public:
		GameObject(GameObjectDesc desc);
		~GameObject();

		// Component methods
		void						addComponent(ComponentType::type, Component* = nullptr);
		RenderComponent*			getRenderComponent();
		LogicComponent*				getLogicComponent();
		InputComponent*				getInputComponent();
		BoxColliderComponent*		getBoxColliderComponent();

		void						addChild(GameObject* child );
	
	
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

};

// GameObject.cpp

int GameObject::GameObjectCounter = 0;

GameObject::GameObject(GameObjectDesc desc)
	: mChildren()
	, mRenderComponent(nullptr)
	, mLogicComponent(nullptr)
	, mBoxColliderComponent(nullptr)
	, mInputComponent(nullptr)
	, mParent(nullptr)
	, mState(nullptr)
{
	
	mChildren.reserve(300);
	
	HRESULT l_result = CoCreateGuid(&mID);
	mName = desc.mName;
	mLayerName = desc.mLayerName;

	// constructing component from Game Object Desc struct
	if(desc.mComponentType & ComponentType::BoxColliderComponent)
	{
		if(desc.mComponentScript != nullptr)
			mBoxColliderComponent = std::move(dynamic_cast<BoxColliderComponent*>(desc.mComponentScript));
		else
			mBoxColliderComponent = std::unique_ptr<BoxColliderComponent>(new BoxColliderComponent(this)).release();
	}

	if(desc.mComponentType & ComponentType::LogicComponent)
	{
		if(desc.mComponentScript != nullptr)
			mLogicComponent = std::move(dynamic_cast<LogicComponent*>(desc.mComponentScript));
		else
			mLogicComponent = std::unique_ptr<LogicComponent>(new LogicComponent(this)).release();
	}

	if(desc.mComponentType & ComponentType::RenderComponent)
	{
		if(desc.mComponentScript != nullptr)
			mRenderComponent = std::move(dynamic_cast<RenderComponent*>(desc.mComponentScript));
		else
			mRenderComponent = std::unique_ptr<RenderComponent>(new RenderComponent(this)).release();
	}

	

	if(desc.mComponentType & ComponentType::InputComponent)
	{
		if(desc.mComponentScript != nullptr)
			mInputComponent = std::move(dynamic_cast<InputComponent*>(desc.mComponentScript));
		else
			mInputComponent = std::unique_ptr<InputComponent>(new InputComponent(this)).release();
	}

	


	// add to sceneLayers
	if(mLayerName != Layer::Root && mLayerName != Layer::Layer)
	{
		for(int j = 0; j < System::mSceneLayers.size(); j++)
		{
			if(System::mSceneLayers[j]->mName == mLayerName)
			{
				
				System::mSceneLayers[j]->addChild(this);
				break;
			}
		}
	}

	// move ownership to System::mGameObjects vector
	if( mLayerName != Layer::Root && mLayerName != Layer::Layer)
	{
		System::mGameObjects.push_back(std::move(std::unique_ptr<GameObject>(this)));
	}

	GameObjectCounter++;
}