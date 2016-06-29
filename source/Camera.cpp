#include "Camera.h"

Camera::Camera() {
	mPositionX = 0;
	mPositionY = 0;
	mCameraWidth = 0;
	mCameraHeight = 0;
}

Camera::Camera(int x, int y, int w, int h) {
	mPositionX = x;
	mPositionY = y;
	mCameraWidth = w;
	mCameraHeight = h;
}

SDL_Rect Camera::GetCameraAsRect()
{
	SDL_Rect rect;
	rect.x = mPositionX;
	rect.y = mPositionY;
	rect.w = mCameraWidth;
	rect.h = mCameraHeight;
	return rect;
}
