
#include "stdafx.h"
#include "SDL_Setup.h"


CSDL_Setup::CSDL_Setup(bool* quit, int ScreenWidth, int ScreenHeight)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = NULL;
	window = SDL_CreateWindow("My first rpg!", 100, 100, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE); //NOT
	mainEvent = new SDL_Event();

	if (window == NULL)
	{
		cout << "windows can not be created\n" << endl;
		*quit = true;
	}

	renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

}


CSDL_Setup::~CSDL_Setup()
{

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	delete mainEvent;
}

//getter 
SDL_Renderer* CSDL_Setup::GetRenderer()
{
	return renderer;
}

SDL_Event* CSDL_Setup::GetMainEvent()
{
	return mainEvent;
}

void CSDL_Setup::Begin()
{
	SDL_PollEvent(mainEvent);

	SDL_RenderClear(renderer); //this clears the screen


}
void CSDL_Setup::End()
{
	SDL_RenderPresent(renderer);

}

