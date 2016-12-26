#include "Renderer.h"

using namespace std;


Renderer::Renderer(SDL_Window* w)
{
	this->window = w;

	//	GL Context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	this->context = SDL_GL_CreateContext(this->window);
	if (this->context == NULL) {
		printf("%s\n", SDL_GetError());
		return;
	}

	//	Prepare extensions
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		printf("ERROR: Could not initialize GLEW - %s\n", glewGetErrorString(glewError));
	}

	Material bland;
	bland.loadProgram("smoothVertex", "smoothFrag");

	//	Initial clear
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(this->window);
}


Renderer::~Renderer()
{
}

void Renderer::render(Scene scene, Uint32 startTime, Uint32 budget)
{
	glClearColor(.8, .2, .5, 1);
}

void Renderer::frameDone(void)
{
	SDL_GL_SwapWindow(this->window);
	glClear(GL_COLOR_BUFFER_BIT);
}




