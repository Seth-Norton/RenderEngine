#pragma once
#include "Model.h"


class Scene
{
public:
	Scene();
	~Scene();

	Model* getAllModels();
	void addModel(Model* newModel);

private:
	Model* models;
};

