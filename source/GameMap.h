#pragma once
#include "TileSet.h"
#include "sdl.h"
#include <iostream>
#include <fstream>
#include "ResourcePaths.h"
#include "TmxMapLoader.h"


class GameMap {

public:

	GameMap() {}
	~GameMap() {}

	bool LoadMapFromTmx(SDL_Renderer* renderHandle, std::string path);
	void RenderMap(SDL_Renderer* renderHandle, SDL_Rect* cameraRectangle);

private:

	std::string loadXMLString(std::string path);
	void loadTmxMap(std::string path);
	void loadTileSets(SDL_Renderer* renderHandle, std::vector<TmxMapTileset>& tilesets);
	int findTilesetIndex(int key);

	std::vector<TileSet*> tileSets;
	std::vector<int> tileSetFirstIdLookup;

	TmxMap map;

	int mapWidthPx;
	int mapHeightPx;

	int NrOfTilesInLayer;

	int NrOfLayers;

	SDLTexture testTex;

};