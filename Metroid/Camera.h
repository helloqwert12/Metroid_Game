#pragma once
#include "Parameters.h"
class Camera
{
public:
	static int max_x;
	static int min_x;

	static int max_y;
	static int min_y;

	static int currentCamX;
	static int currentCamY;

	static int width;	// width của viewport
	static int height;	// height của viewport

	Camera();
	~Camera();

	static void SetCameraX(int pos_x);
	static void SetCameraY(int pos_y);

	static void SetDemension(int mode);
};

