#include "Camera.h"

int Camera::currentCamX = 0;
int Camera::currentCamY = 0;

int Camera::max_x = 2000;
int Camera::min_x = 0;

int Camera::max_y = 0;
int Camera::min_y = 0;

int Camera::width = 640;
int Camera::height = 480;

Camera::Camera()
{
	Camera::SetDemension(GAME_SCREEN_RESOLUTION_640_480_24);
}


Camera::~Camera()
{
}

void Camera::SetCameraX(int pos_x)
{
	currentCamX = pos_x - 320;
	if (currentCamX < min_x)
	{
		currentCamX = min_x;
	}
	if (currentCamX + width >= max_x)
	{
		currentCamX = max_x - width;
	}
}

void Camera::SetCameraY(int pos_y)
{
	if (max_y == 0)
	{
		currentCamY = 500;
		return;
	}
	/*if (currentCamY < min_y)
	{
		currentCamY = min_y;
	}
	if (currentCamY >= max_y)
	{
		currentCamY = max_y;
	}*/
}

void Camera::SetDemension(int mode)
{
	switch (mode)
	{
	case GAME_SCREEN_RESOLUTION_640_480_24:
		width = 640;
		height = 480;
		break;
	case GAME_SCREEN_RESOLUTION_800_600_24:
		width = 800;
		height = 600;
		break;
	case GAME_SCREEN_RESOLUTION_1024_768_24:
		width = 1024;
		height = 768;
		break;
	}
}

//void Camera::SetCameraY()
//{
//	int result = 600;
//	return result;
//}
