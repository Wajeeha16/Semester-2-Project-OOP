#pragma once
#include "stdafx.h"
#include "SDL_Setup.h"
#include "Sprite.h"
#include "Tree.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

class CEnvironment
{
public:
	CEnvironment(int ScreenWidth, int SreenHeight, float *CameraX, float *CameraY, CSDL_Setup* csdl_Setup);
	~CEnvironment();

	void DrawBack();
	void DrawFront();

	void Update();

	void SaveToFile();
	void LoadFromFile();
	enum ModeType
	{
		GamePlay,
		LevelCreation
	};

	std::vector<Tree*> GetTrees(){ return trees; }


private:
	int Mode;
	CSDL_Setup* csdl_setup;
	float *CameraX;
	float *CameraY;
	bool OnePressed;
	CSprite* grass[4][7];
	std::vector<Tree*> trees;

};

