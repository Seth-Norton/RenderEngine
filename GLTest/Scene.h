#pragma once
#include "GL/glew.h"

#include "Model.h"


class Scene
{
public:
	Scene();
	~Scene();

	Model** getModels();
	GLuint numModels();
	void addModel(Model* newModel);

private:
	GLuint allowedModels = 8;
	Model** models = nullptr;
	GLuint n = 0;
};

