#include "Environment.h"



CEnvironment::CEnvironment(int ScreenWidth, int ScreenHeight, float *passed_CameraX, float *passed_CameraY, CSDL_Setup* passed_csdl_Setup)
{
	csdl_setup = passed_csdl_Setup;
	CameraX = passed_CameraX;
	CameraY = passed_CameraY;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			grass[i][j] = new CSprite(csdl_setup->GetRenderer(), "grass.bmp", ScreenWidth * i, ScreenHeight * j, ScreenWidth, ScreenHeight, CameraX, CameraY, CCollisionRectangle());
		}
	};

	Mode = LevelCreation;
	LoadFromFile();
	OnePressed = false;
	
	
	//tree = new Tree(300, 300, CameraX, CameraY, csdl_setup);
	
	/*for (int i = 0; i < 20; i++){
		 trees.push_back(new Tree(300 + (200 * i), 300 + (200 * i), CameraX, CameraY, csdl_setup));
	}*/
	

}


CEnvironment::~CEnvironment()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			delete grass[i][j];
		}
	}

	for (std::vector<Tree*>::iterator itr = trees.begin(); itr != trees.end(); ++itr){
		delete (*itr);
	}
	trees.clear();
}

void CEnvironment::DrawBack()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			grass[i][j]->draw();

		}
	}
	//tree->DrawTrunk();

	for (std::vector<Tree*>::iterator itr = trees.begin(); itr != trees.end(); ++itr){
		(*itr)->DrawTrunk();
	}
}


void CEnvironment::DrawFront()
{
	for (std::vector<Tree*>::iterator itr = trees.begin(); itr != trees.end(); ++itr)
	{
		(*itr)->DrawCrown();
	}

}

void CEnvironment::LoadFromFile()
{
	std::ifstream LoadedFile("StageLayout.txt");

	std::string line;

	enum ObjectType{
		TypeNone,
		TypeTree
	};

	int CurrentType = TypeNone;

	if (LoadedFile.is_open())
	{
		while (LoadedFile.good())
		{
			std::getline(LoadedFile, line);
			if (line == "----BEGIN_TREE----")
			{
				CurrentType = TypeTree;
			}
			else if (line == "----END_TREE----")
			{
				CurrentType = TypeNone;
			}
			else
			{
				if (CurrentType == TypeTree)
				{
					std::istringstream iss(line);

					int TempX = 0;
					int TempY = 0;
					std::string PreviousWord = "";

					while (iss)
					{
						std::string word;
						iss >> word;
						if (PreviousWord == "x:")
						{
							TempX = atoi(word.c_str());
							std::cout << "X is" << TempX << std::endl;
						}
						if (PreviousWord == "y:")
						{
							TempY = atoi(word.c_str());
							trees.push_back(new Tree(TempX, TempY, CameraX, CameraY, csdl_setup));

						}
						PreviousWord = word;
					}
				}
			}
		}
	}
	else
	{
		std::cout << "File could not be opened: StageLayout.txt" << std::endl;
	}
}



void CEnvironment::SaveToFile()
{
	std::ofstream LoadedFile;
	LoadedFile.open("StageLayout.txt");

	LoadedFile << "----BEGIN_TREE----" << std::endl;

	for (std::vector<Tree*>::iterator itr = trees.begin(); itr != trees.end(); ++itr)
	{
		//(*itr)->DrawCrown();
		LoadedFile << "x:" << (*itr)->GetX() << "\ty:" << (*itr)->GetY() << std::endl;

	}

	LoadedFile << "----END_TREE----" << std::endl;

	std::cout << "Level saved." << std::endl;
	LoadedFile.close();
}

void CEnvironment::Update()
{
	if (Mode == LevelCreation){
		
		if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
		{
			
			if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_3)
			{
				SaveToFile();
				OnePressed = true;
			}
		}

		if (csdl_setup->GetMainEvent()->type == SDL_KEYUP)
		{
			if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_3)
			{
				OnePressed = false;
			}
		}

		if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
		{
			if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_1)
			{
				std::cout << "one" << std::endl;
				trees.push_back(new Tree(-*CameraX + 250, -*CameraY + 90, CameraX, CameraY, csdl_setup));
				OnePressed = true;
			}
		}

		if (csdl_setup->GetMainEvent()->type == SDL_KEYUP)
		{
			if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_1)
			{
				OnePressed = false;
			}
		}
	}

	if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
	{
		if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_2)
		{
			if (Mode == LevelCreation){
				std::cout << "Level Creation OFF" << std::endl;
				Mode = GamePlay;
			}
			else if (Mode == GamePlay){
				std::cout << "Level Creation ON" << std::endl;

				Mode = LevelCreation;
			}
			std::cout << "one" << std::endl;
			OnePressed = true;
		}
	}

	if (csdl_setup->GetMainEvent()->type == SDL_KEYUP)
	{
		if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_2)
		{
			OnePressed = false;
		}
	}
}