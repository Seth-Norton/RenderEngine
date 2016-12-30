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
	SDL_Window* window = nullptr;
	SDL_GLContext context;

	GLuint material;

	Uint32 prevFrame = 0;
	Uint32 avgFrame = 0;
	Uint32 prevUpdate = 0;
	Uint32 FPS_UPDATE_INTERVAL = 10;
	Uint32 time = 0;
	Uint32 eTime = 0;
	Uint32 updateTime = 0;

	
};

