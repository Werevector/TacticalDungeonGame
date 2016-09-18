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
	int GetMapWidth() { return map.mWidth; }
	int GetMapHeight() { return map.mHeight; }
	int GetNumberOfLayers() { return map.mLayers.size(); }
	int GetLayerOffset(int i) { return map.mLayers[i].mOffsety; }
	int GetNrOfTilesInLayer() { return NrOfTilesInLayer; }
	std::vector<std::vector<int>> GetWeightLayers() { return mWeightMap; }

private:

	std::string loadXMLString(std::string path);
	void loadTmxMap(std::string path);
	void loadTileSets(SDL_Renderer* renderHandle, std::vector<TmxMapTileset>& tilesets);
	void calculateWeightMap();
	int findTilesetIndex(int key);
	std::vector<int> loadWeightLookupTable(std::string path);

	std::vector<TileSet*> tileSets;
	std::vector<int> tileSetFirstIdLookup;

	TmxMap map;

	std::vector<std::vector<int>> mWeightLookupTables;
	std::vector<std::vector<int>> mWeightMap;

	int mapWidthPx;
	int mapHeightPx;
	int NrOfTilesInLayer;
	int NrOfLayers;

	int isoMapWidthPx;
	int isoMapHeightPx;

};