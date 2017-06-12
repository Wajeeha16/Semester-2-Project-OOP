#include "stdafx.h"
#include "Main.h"
#include "Tree.h"


CMain::CMain(int Passed_ScreenWidth, int passed_ScreenHeight)
{
	CameraX = 0;
	CameraY = 0;
	ScreenWidth = Passed_ScreenWidth;
	ScreenHeight = passed_ScreenHeight;
	quit = false;
	csdl_setup = new CSDL_Setup(&quit, ScreenWidth, ScreenHeight);


	ForestArea = new CEnvironment(ScreenWidth, ScreenHeight, &CameraX, &CameraY, csdl_setup);


	

	mouseX = 0;
	mouseY = 0;
	bob = new MainCharacter(csdl_setup, &mouseX, &mouseY, &CameraX, &CameraY, ForestArea);
}


CMain::~CMain()
{
	delete csdl_setup;

	delete bob;

}



void CMain::GameLoop(void)
{
	while (!quit && csdl_setup->GetMainEvent()->type != SDL_QUIT) //quit==false // windows stuck in the loop cant close... we are not updaating sdl
	{

		csdl_setup->Begin();

		//position of mouse

		SDL_GetMouseState(&mouseX, &mouseY);
		
		ForestArea->DrawBack();
		ForestArea->Update();
		bob->Draw();
		


		bob->Update();

		ForestArea->DrawFront();
		csdl_setup->End();
	}


}
