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

	//	VSync
	SDL_GL_SetSwapInterval(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	Material bland;
	if(!bland.loadProgram("smoothVertex.glsl", "smoothFrag.glsl"))	//	In case of failure, load default textures
		bland.loadDefault();

	//	Initial clear
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(this->window);


	//	Prepare timing
	this->prevFrame = SDL_GetTicks();
	this->avgFrame = 17;
	this->prevUpdate = SDL_GetTicks();
}


Renderer::~Renderer()
{
}

void Renderer::render(Scene scene, Uint32 startTime, Uint32 budget)
{
	Model** models = scene.getModels();
	GLuint numModels = scene.numModels();

	SDL_GL_MakeCurrent(this->window, this->context);

	glEnable(GL_DEPTH_TEST);
	
	//	Debug
	/*glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 1);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.87f, -0.5f, 0.0f);
	glVertex3f(-0.87f,-0.5f, 0.0f);
	glEnd();*/

	GLuint drawnTriangles = 0;

	for (GLuint i = 0; i < numModels; i++) {
		glBindVertexArray(models[i]->vao());
		glDrawElements(GL_TRIANGLES, models[i]->numFaces() * 3, GL_UNSIGNED_INT, (void*)0);
		drawnTriangles += models[i]->numFaces();
	}
	glBindVertexArray(0);
	

	glDisable(GL_DEPTH_TEST);
	


	//	Time Handling
	this->time = SDL_GetTicks();
	this->eTime = this->time - this->prevFrame;
	this->avgFrame = 0.4*this->avgFrame + 0.6*this->eTime;
	this->updateTime = this->time - this->prevUpdate;
	if (this->avgFrame > 0 && this->updateTime > this->FPS_UPDATE_INTERVAL*this->avgFrame) {
		printf("%d triangles: %d msecs, %4.1f FPS\r", drawnTriangles, this->avgFrame, 1.0f / (float)this->avgFrame*1000.0f);
		this->prevUpdate = this->time;
	}
	this->prevFrame = this->time;
}

void Renderer::frameDone(void)
{
	glClearColor(.8, .2, .5, 1);
	SDL_GL_SwapWindow(this->window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}




