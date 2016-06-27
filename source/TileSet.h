#pragma once
#include "SDLTexture.h"
#include "sdl.h"
#include <string>
#include <vector>

class TileSet {

public:

	TileSet() {};
	TileSet(std::string, int);
	~TileSet();

	bool LoadTileSetFromFile(
		SDL_Renderer* renderer,
		std::string path,
		int tileWidthPx,
		int tileHeightPx);

	bool LoadTileSetFromFile(SDL_Renderer* renderer, std::string path, std::string metaDataPath);

	void RenderFromSheet(
		SDL_Renderer* renderer, 
		int x, 
		int y, 
		int key, 
		SDL_Rect* target, 
		double angle,
		SDL_RendererFlip flip);

	std::string GetName() { return name; }
	int GetFirstId() { return firstId; }
	void SetName(std::string n) { name = n; }
	void SetfirstId(int i) { firstId = i; }

private:

	std::vector<SDL_Rect*> sheetClips;
	SDLTexture textureSheet;

	std::string name;
	int firstId;

	int tileWidth;
	int tileHeight;
	int tileNrX;
	int tileNrY;

};