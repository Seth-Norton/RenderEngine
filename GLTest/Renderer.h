#pragma once
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "sdl/SDL.h"
#undef main

#include "Standard.h"
#include "Scene.h"
#include "Model.h"
#include "Material.h"


class Renderer
{
public:
	Renderer(SDL_Window* window);
	~Renderer();
	void render(Scene scene, Uint32 startTime, Uint32 budget);
	void frameDone(void);

private:
	SDL_Window* window;
	SDL_GLContext context;

	GLuint material;


	
};

