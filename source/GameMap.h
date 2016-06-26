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

	bool LoadMapFromTmx(SDL_Renderer* renderHandle, std::string path);

private:

	std::string loadXMLString(std::string path);
	NLTmxMap* loadTmxMap(std::string path);
	std::vector<TileSet> loadTileSets(SDL_Renderer* renderHandle, std::vector<NLTmxMapTileset*> tilesets);




	std::vector<TileSet> tileSets;
	TileSet mapTileSet;
	
	int mapWidth;
	int mapHeight;
	int mapWidthPx;
	int mapHeightPx;

	int tileWidth;
	int tileHeight;

	int NrOfTilesInLayer;

	int NrOfLayers;

};