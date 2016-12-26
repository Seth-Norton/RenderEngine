#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

Model * Scene::getAllModels()
{
	return nullptr;
}

void Scene::addModel(Model * newModel)
{
	models = newModel;
}
