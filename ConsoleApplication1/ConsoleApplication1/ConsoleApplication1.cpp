#include "stdafx.h"
#include "Main.h"


int main(int argc, char* argv[])
{
	CMain* cmain = new CMain(1000, 800);
	cmain->GameLoop();
	
	delete cmain;

	return 0;
}

