#pragma once
#include "Standard.h"
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "sdl/SDL.h"
#undef main

#include "Scene.h"
#include "Model.h"


class Material
{
public:
	Material();
	~Material();

	

	bool loadProgram(const char* vertexFilepath, const char* fragFilepath);

private:
	void printProgramLog(GLuint program);
	void printShaderLog(GLuint shader);
};

