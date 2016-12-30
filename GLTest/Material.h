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
	bool loadDefault();

private:
	GLuint program = 0;

	void printProgramLog(GLuint program);
	void printShaderLog(GLuint shader);

	bool loadSources(const GLchar** vertexSource, const GLchar** fragSource);
	
};

