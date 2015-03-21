#include "Scene.h"
#include "SceneStack.h"
Scene::Scene(SceneStack& stack, Context& context)
	: mStack(&stack)
	, mContext(context)
{


}

void Scene::requestStackPop()
{
	mStack->popScene();
}

void Scene::requestStackPush(Scenes::ID stateID)
{
	mStack->pushScene(stateID);

}

void Scene::requestStackClear()
{
	mStack->clearScenes();

}
Scene::Context& Scene::getContext()
{
	return mContext;
}