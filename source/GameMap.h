#pragma once
#include "TileSet.h"
#include "NLTmxMap.h"
#include "sdl.h"
#include <iostream>
#include <fstream>
#include "ResourcePaths.h"


class GameMap {

public:

	GameMap() {}
	~GameMap() {}

	bool LoadMapFromTmx(SDL_Renderer* renderHandle, std::string path);
	void RenderMap(SDL_Renderer* renderHandle);

private:

	std::string loadXMLString(std::string path);
	NLTmxMap* loadTmxMap(std::string path);
	void loadTileSets(SDL_Renderer* renderHandle, std::vector<NLTmxMapTileset*> tilesets);
	int findTilesetIndex(int key);

	std::vector<TileSet*> tileSets;
	std::vector<int> tileSetFirstIdLookup;

	NLTmxMap* map;

	int mapWidthPx;
	int mapHeightPx;

	int NrOfTilesInLayer;

	int NrOfLayers;

	SDLTexture testTex;

};