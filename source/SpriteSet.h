#pragma once
#include "SDLTexture.h"
#include "sdl.h"
#include "SDLTexture.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class SpriteSet {

public:
	SpriteSet();
	~SpriteSet();
	bool LoadSpriteSetFromFile(SDL_Renderer* renderHandle, std::string imagePath, std::string metaPath);
	void RenderSpriteFromKey(SDL_Renderer* renderHandle, int x, int y, int key);
	int GetAmountOfClips();

	int mWidthPx;
	int mHeightPx;

private:

	bool GenerateClipsFromMeta(std::string metaPath);

	SDLTexture spriteSheet;
	std::vector<SDL_Rect> spriteClips;

};