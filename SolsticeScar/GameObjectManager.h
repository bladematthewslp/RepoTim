#ifndef GAMEOBJECTMANAGER_H_
#define GAMEOBJECTMANAGER_H_

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <vector>
#include <array>
#include <sstream>
#include <string>
#include <map>
#include <unordered_map>


class GameObjectManager
{

public:
	GameObjectManager();
	void										init();
	static GameObject							mSceneGraphRoot;
	static std::vector<GameObject*>				gameLayers;
	static std::map<std::string, GameObject*>	sceneLayers;
	


	static void addToLayer(GameObject* gameObject, Layer::Name);
	void createGameObjectGraph(std::vector<GameObject*>&);
	
	
	
	static void renderSceneGraph(sf::RenderWindow& window);



};



#endif // GAMEOBJECTMANAGER_H_