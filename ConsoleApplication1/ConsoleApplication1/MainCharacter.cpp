#include "MainCharacter.h"


MainCharacter::MainCharacter(CSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, float *passed_CameraX, float *passed_CameraY, CEnvironment* passed_Environment)
{
	Environment = passed_Environment;
	CameraX = passed_CameraX;
	CameraY = passed_CameraY;


	csdl_setup = passed_SDL_Setup;
	MouseX = passed_MouseX;
	MouseY = passed_MouseY;

	bob = new CSprite(csdl_setup->GetRenderer(), "tom.png", 300, 250, 150, 120, CameraX, CameraY, CCollisionRectangle(275, 220, 50, 30));

	bob->SetUpAnimation(4, 4);
	bob->SetOrigin(bob->GetWidth() / 2.0f, bob->GetHeight() / 2.0f);
	timeCheck = SDL_GetTicks();

	Follow = false;

	distance = 0;
	stopAnimation = false;




}


MainCharacter::~MainCharacter()
{
	delete bob;
}

void MainCharacter::Draw()
{
	bob->DrawSteady();
}

void MainCharacter::UpdateAnimation()
{

	float angle = atan2(Follow_Point_Y - *CameraY, Follow_Point_X - *CameraX);
	angle = angle*(180 / 3.14) + 180;

	//cout << angle << endl;

	if (!stopAnimation)
	{
		if (angle > 45 && angle <= 135)
		{
			//down
			if (distance > 15)
				bob->PlayAnimation(0, 3, 0, 200);
			else
				bob->PlayAnimation(0, 1, 0, 200);
		}
		else if (angle > 135 && angle <= 225)
		{
			//left
			if (distance > 15)
				bob->PlayAnimation(0, 3, 1, 200);
			else
				bob->PlayAnimation(1, 1, 1, 200);



		}
		else if (angle > 225 && angle <= 315)
		{
			//Up
			if (distance > 15)
				bob->PlayAnimation(0, 3, 3, 200);
			else
				bob->PlayAnimation(1, 1, 3, 200);


		}
		else if ((angle <= 360 && angle > 315) || (angle >= 0 && angle <= 45))
		{
			//right
			if (distance > 15)
				bob->PlayAnimation(0, 3, 2, 200);
			else
				bob->PlayAnimation(1, 1, 2, 200);

		}
	}
}


void MainCharacter::UpdateControls()
{
	//bob->PlayAnimation(0, 3, 1, 200);

	if (csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN || csdl_setup->GetMainEvent()->type == SDL_MOUSEMOTION)
	{
		if (csdl_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
		{
			Follow_Point_X = *CameraX - *MouseX + 300;
			Follow_Point_Y = *CameraY - *MouseY + 250;

			Follow = true;
		}
	}

	//GAME CONTROL WITH KEYBOARD
	/*switch (csdl_setup->GetMainEvent()->type)
	{

	case SDL_KEYDOWN:
	switch (csdl_setup->GetMainEvent()->key.keysym.sym)
	{

	case SDLK_a:

	MoveLeft = true;


	break;
	case SDLK_s:
	MoveDown = true;


	break;
	case SDLK_w:


	MoveUp = true;

	break;
	case SDLK_d:
	MoveRight = true;


	break;
	default:
	break;
	}
	break;

	case SDL_KEYUP:
	switch (csdl_setup->GetMainEvent()->key.keysym.sym)
	{

	case SDLK_a:

	MoveLeft = false;


	break;
	case SDLK_s:
	MoveDown = false;


	break;
	case SDLK_w:


	MoveUp = false;

	break;
	case SDLK_d:
	MoveRight = false;


	break;
	default:
	break;
	}
	break;
	default:
	break;

	}
	*/
	if (timeCheck + 10 < SDL_GetTicks() && Follow)
	{

		distance = GetDistance(*CameraX, *CameraY, Follow_Point_X, Follow_Point_Y);


		if (distance == 0)
			stopAnimation = true;
		else
			stopAnimation = false;

		if (distance > 15)
		{
			bool colliding = false;
			for (int i = 0; i < Environment->GetTrees().size(); i++)
			{
				if (bob->isColliding(Environment->GetTrees()[i]->GetTrunk()->GetCollisionRect()))
				{
					if (*CameraX > Follow_Point_X)
					{
						*CameraX = *CameraX + 5;
					}
					if (*CameraX < Follow_Point_X)
					{
						*CameraX = *CameraX - 5;
					}
					if (*CameraY > Follow_Point_Y)
					{
						*CameraY = *CameraY + 5;
					}
					if (*CameraY < Follow_Point_Y)
					{
						*CameraY = *CameraY - 5;
					}
					Follow_Point_X = *CameraX;
					Follow_Point_Y = *CameraY;
					distance = 0;
					Follow = false;

					colliding = true;
					//std::cout << "Colliding with a tree." << std::endl;
				}
			}

			if (!colliding)
			{

				if (*CameraX != Follow_Point_X)
				{
					*CameraX = *CameraX - (((*CameraX - Follow_Point_X) / distance)* 1.5f);

				}
				//if (bob->GetX() < Follow_Point_X)
				//{
				//	bob->SetX(bob->GetX() - ((bob->GetX() - Follow_Point_X) / distance)* 1.5f);
				//}

				if (*CameraY != Follow_Point_Y)
				{
					*CameraY = *CameraY - (((*CameraY - Follow_Point_Y) / distance)* 1.5f);

				}
			}
			//if (bob->GetY() < Follow_Point_Y)
			//{
			//	bob->SetY(bob->GetY() - ((bob->GetY() - Follow_Point_Y) / distance)* 1.5f);

			//}
		}
		else
			Follow = false;
		timeCheck + 500 > SDL_GetTicks();
	}

}

void MainCharacter::Update()
{
	UpdateAnimation();

	UpdateControls();
	
}

double MainCharacter::GetDistance(int X1, int Y1, int X2, int Y2)
{
	double DifferenceX = X1 - X2;
	double DifferenceY = Y1 - Y2;
	//get distnace between two points
	double distance = sqrt(DifferenceX*DifferenceX + DifferenceY*DifferenceY);
	return distance;
}

