#pragma once
#include "sdl.h"
#include "sdl_image.h"
#include "sdl_ttf.h"
#include <string>

class SDLTexture {
public:
	
	SDLTexture();
	~SDLTexture();

	bool LoadFromImgFile(SDL_Renderer*, std::string path);
	bool LoadFromRenderedText(SDL_Renderer* gRenderer, TTF_Font* gFont, std::string textureText, SDL_Color textColor);
	void RenderTexture(
		SDL_Renderer*, 
		int x, 
		int y, 
		SDL_Rect* clip = NULL, 
		SDL_Rect* dstnrect = NULL, 
		double angle = 0.0, 
		SDL_Point* center = NULL, 
		SDL_RendererFlip flip = SDL_FLIP_NONE);

	void FreeTexture();

	int getWidth()	{ return  mWidth; }
	int getHeight() { return mHeight; }

private:

	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;

	bool textMode = false;

};