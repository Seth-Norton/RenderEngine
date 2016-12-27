#include "Scene.h"



Scene::Scene()
{
	this->n = 0;
	this->models = (Model**)malloc(allowedModels * sizeof(Model*));
}


Scene::~Scene()
{
}

Model** Scene::getModels()
{
	return this->models;
}

GLuint Scene::numModels()
{
	return this->n;
}

void Scene::addModel(Model* newModel)
{
	//	TODO: Initiate file loading in separate thread

	if (n + 1 > allowedModels) {
		allowedModels *= 2;
		Model** oldPointer = this->models;

		this->models = (Model**)malloc(allowedModels * sizeof(Model*));
		memcpy(this->models, oldPointer, n * sizeof(Model*));
		free(oldPointer);
	}

	//printf("%d/%d models\n", n+1, allowedModels);

	this->models[n] = newModel;
	this->n++;
}
