#pragma once
#include "sdl.h"

class Camera {
public:

	Camera();
	Camera(int x, int y, int w, int h);
	SDL_Rect GetCameraAsRect();

	int mPositionX;
	int mPositionY;
	int mCameraWidth;
	int mCameraHeight;

};