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

	int GetMapTileWidth() { return map.mTileWidth; }
	int GetMapTileHeight() { return map.mTileHeight; }
	int GetNumberOfLayers() { return map.mLayers.size(); }
	int GetLayerOffset(int i) { return map.mLayers[i].mOffsety; }

private:

	std::string loadXMLString(std::string path);
	void loadTmxMap(std::string path);
	void loadTileSets(SDL_Renderer* renderHandle, std::vector<TmxMapTileset>& tilesets);
	std::vector<int> loadWeightLookupTable(std::string path);
	int findTilesetIndex(int key);

	std::vector<TileSet*> tileSets;
	std::vector<int> tileSetFirstIdLookup;

	TmxMap map;

	std::vector<std::vector<int>> mWeightLookupTables;

	int mapWidthPx;
	int mapHeightPx;
	int NrOfTilesInLayer;
	int NrOfLayers;

	int isoMapWidthPx;
	int isoMapHeightPx;

};