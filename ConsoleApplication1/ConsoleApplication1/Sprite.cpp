#include "Sprite.h"



CSprite::CSprite(SDL_Renderer* passed_renderer, string FilePath, int x, int y, int w, int h, float *passed_CameraX, float *passed_CameraY, CCollisionRectangle passed_CollisionRect)
{
	CollisionRect = passed_CollisionRect;
	renderer = passed_renderer;
	image = NULL;
	image = IMG_LoadTexture(renderer, FilePath.c_str());

	if (image == NULL)
	{
		cout << "couldnt load image" << FilePath.c_str() << endl;
	}

	CollisionImage = NULL;
	CollisionImage = IMG_LoadTexture(renderer, FilePath.c_str());

	if (CollisionImage == NULL)
	{
		cout << "couldnt load image" << "CollisionImage" << endl;
	}

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	//set bob to actual size of BG image
	SDL_QueryTexture(image, NULL, NULL, &img_width, &img_height);

	crop.x = 0;
	crop.y = 0;
	crop.w = img_width;
	crop.h = img_height;




	X_pos = x;
	Y_pos = y;

	origin_x = 0;
	origin_y = 0;

	CurrentFrame = 0;
	Amount_Frame_X = 0;
	Amount_Frame_Y = 0;

	CameraX = passed_CameraX;
	CameraY = passed_CameraY;

	Camera.x = rect.x + *CameraX;
	Camera.y = rect.y + *CameraY;

	Camera.w = rect.w;
	Camera.h = rect.h;

}
//I Was hererere
void CSprite::SetUpAnimation(int passed_Amount_X, int passed_Amount_Y)
{
	Amount_Frame_X = passed_Amount_X;
	Amount_Frame_Y = passed_Amount_Y;
}
;

void CSprite::PlayAnimation(int BeginFrame, int EndFrame, int Row, float Speed)
{
	if (animationDelay + Speed < SDL_GetTicks())
	{
		//lets just crop it
		if (EndFrame <= CurrentFrame)
			CurrentFrame = BeginFrame;
		else
			CurrentFrame++;


		crop.x = CurrentFrame * (img_width / Amount_Frame_X);
		crop.y = Row* (img_height / Amount_Frame_Y);
		crop.w = img_width / Amount_Frame_X;   //was 3
		crop.h = img_height / Amount_Frame_Y;
		animationDelay = SDL_GetTicks();
	}
}




CSprite::~CSprite()
{
	SDL_DestroyTexture(image);
}

void CSprite::draw()
{
	Camera.x = rect.x + *CameraX;
	Camera.y = rect.y + *CameraY;

	Camera.w = rect.w;
	Camera.h = rect.h;

	CollisionRect.SetX(rect.x + *CameraX);
	CollisionRect.SetY(rect.y + *CameraY);

	SDL_RenderCopy(renderer, image, &crop, &Camera);
	SDL_RenderCopy(renderer, CollisionImage, NULL, &CollisionRect.GetRectangle());



}

void CSprite::DrawSteady()
{
	SDL_RenderCopy(renderer, image, &crop, &rect);
	SDL_RenderCopy(renderer, CollisionImage, NULL, &CollisionRect.GetRectangle());

}

void CSprite::SetX(float X)
{
	X_pos = X;

	rect.x = int(X_pos - origin_x);

}
void CSprite::SetY(float Y)
{
	Y_pos = Y;

	rect.y = int(Y_pos - origin_x);

}

void CSprite::SetPosition(float X, float Y)
{
	X_pos = X;
	Y_pos = Y;

	rect.x = int(X_pos - origin_x);
	rect.y = int(Y_pos - origin_y);

}

float CSprite::GetX()
{
	return X_pos;
}

float CSprite::GetY()
{
	return Y_pos;
}

void CSprite::SetOrigin(float X, float Y)
{
	origin_x = X;
	origin_y = Y;
	SetPosition(GetX(), GetY());

}

void CSprite::SetWidth(int W)
{
	rect.w = W;
}

void CSprite::SetHeight(int H)
{
	rect.h = H;
}


int CSprite::GetWidth()
{
	return rect.w;

}

int CSprite::GetHeight()
{
	return rect.h;
}

bool CSprite::isColliding(CCollisionRectangle theCollider)
{
	return !(CollisionRect.GetRectangle().x + CollisionRect.GetRectangle().w < theCollider.GetRectangle().x || CollisionRect.GetRectangle().y + CollisionRect.GetRectangle().h < theCollider.GetRectangle().y || CollisionRect.GetRectangle().x > theCollider.GetRectangle().x + theCollider.GetRectangle().w || CollisionRect.GetRectangle().y > theCollider.GetRectangle().y + theCollider.GetRectangle().h);
}


