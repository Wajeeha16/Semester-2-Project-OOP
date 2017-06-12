#pragma once
//program runs only once..equal to type def.
#include "SDL_Setup.h"
#include "Sprite.h"
#include "MainCharacter.h"
#include "Environment.h"
#include <math.h>

class CMain
{
public:
	CMain(int Passed_ScreenWidth, int passed_ScreenHeight); //constructor
	~CMain(); //destructor


	void GameLoop();
	//it will get position betweent the points. we are doing this to make the bob move exactly with mouse


private:
	float CameraX;
	float CameraY;


	MainCharacter *bob;
	CEnvironment* ForestArea;


	int ScreenWidth;
	int ScreenHeight;
	bool quit;


	CSDL_Setup* csdl_setup;

	



	//keeping track of mouse position

	int mouseX;
	int mouseY;





};




