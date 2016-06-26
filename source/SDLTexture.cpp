#include "SDLTexture.h"

SDLTexture::SDLTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

SDLTexture::~SDLTexture()
{
	FreeTexture();
}

bool SDLTexture::LoadFromImgFile(SDL_Renderer * renderHandle, std::string path)
{
	FreeTexture();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{

		newTexture = SDL_CreateTextureFromSurface(renderHandle, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return mTexture != NULL;
}

bool SDLTexture::LoadFromRenderedText(SDL_Renderer* gRenderer, TTF_Font* gFont, std::string textureText, SDL_Color textColor)
{
	FreeTexture();

	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
			textMode = true;
		}
		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}


	//Return success
	return mTexture != NULL;
}

void SDLTexture::RenderTexture(SDL_Renderer * gRenderer, int x, int y, SDL_Rect * clip, SDL_Rect * dstnrect, double angle, SDL_Point * center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if (textMode) {
		renderQuad.w = mWidth;
		renderQuad.h = mHeight;
	}
	else {
		renderQuad.w = dstnrect->w;
		renderQuad.h = dstnrect->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void SDLTexture::FreeTexture()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
