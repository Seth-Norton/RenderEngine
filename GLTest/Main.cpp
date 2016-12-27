#include "Standard.h"
#include "Renderer.h"
#include "Model.h"



using namespace std;

bool done = false;


void handleKeys(unsigned char key, int x, int y) {
	done = true;
}




int main()
{
	SDL_Window* window = nullptr;
	SDL_Surface* surface = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("ERROR: Could not initialize SDL - %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow("GLTest", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (window == nullptr)
		printf("%s\n", SDL_GetError());

	surface = SDL_GetWindowSurface(window);
	if (surface == nullptr)
		printf("%s\n", SDL_GetError());


	Renderer mainRend(window);

	Model cube;
	cube.loadBox();

	Scene world;
	world.addModel(&cube);





	


	SDL_Event e;
	while (!done) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				done = true;

			else if (e.type == SDL_TEXTINPUT) {
				int x=0, y=0;
				SDL_GetMouseState(&x, &y);
				handleKeys(e.text.text[0], x, y);
			}
		}

		


		//	Prepare render and flush commands
		mainRend.render(world, SDL_GetTicks(), 15);
		mainRend.frameDone();
	}







	

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

