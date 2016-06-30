#include "GameMap.h"

bool GameMap::LoadMapFromTmx(SDL_Renderer* renderHandle, std::string path)
{
	bool success = true;

	loadTmxMap(path);

	NrOfTilesInLayer = map.mWidth * map.mHeight;

	mapWidthPx = map.mWidth * map.mTileWidth;
	mapHeightPx = map.mHeight * map.mTileHeight;

	NrOfLayers = map.mLayers.size();

	loadTileSets(renderHandle, map.mTilesets);

	//testTex.LoadFromImgFile(renderHandle, paths::PathTilesets() + "iso-64x64-building_2" + ".png");
	return success;
}

void GameMap::RenderMap(SDL_Renderer* renderHandle, SDL_Rect* cameraRectangle)
{
	int key = 0;
	int tilesetIndex = 0;
	float x = 0;
	float y = 0;
	
	SDL_Rect target;
	
	target.x = 0;
	target.y = 0;
	target.w = 64;
	target.h = 64;

	for (int layer = 0; layer < map.mLayers.size(); layer++) 
	{
		for (int tile = 0; tile < NrOfTilesInLayer; tile++) 
		{
			//Only render if the tile exists (non zero)
			if (map.mLayers[layer].mData[tile] != 0) {
				key = map.mLayers[layer].mData[tile] - 1;

				//Finding correct index is needed because of the structure of the tilesets
				//when using multiple tilesets in the same map.
				//Should be reworked
				tilesetIndex = findTilesetIndex(key);
				if (tilesetIndex != 0) {
					key -= tileSets[tilesetIndex]->GetFirstId()-1;
				}
				

				//TODO:: - Rendering in the Texture class uses the target rectangle in a redundant way
				//         A whole SDL_Rect is not required.
				//
				//		 - Tile dimensions are different for texture, and map tiles, this should be clearer


				//Orthographic coordinates
				float Ortho_x = tile / map.mWidth;
				float Ortho_y = tile % map.mHeight;

				//Convert to isometric coordinates
				//TODO: Make a function for this
				x = (Ortho_y - Ortho_x) * (map.mTileWidth / 2);
				y = ((Ortho_y + Ortho_x) * (map.mTileHeight / 2)) + map.mLayers[layer].mOffsety;
				
				//Centering the map in the window
				const int side = map.mHeight + map.mWidth;
				float xwid = side * (map.mTileWidth / 2);
				float yheig = side * (map.mTileHeight / 2);
				x -= map.mTileWidth/2;
				y -= map.mTileHeight;
				y -= yheig / 2;
				x += cameraRectangle->w / 2;
				y += cameraRectangle->h / 2;
				
				tileSets[tilesetIndex]->RenderFromSheet(renderHandle, x, y, key, &target, NULL, SDL_FLIP_NONE);
			}
		}
	}
}

std::string GameMap::loadXMLString(std::string path)
{
	const char* path_c = path.c_str();
	std::ifstream fileStream;
	fileStream.open(path_c);

	if (!fileStream.is_open()) {
		std::cout << "Roomloader failed ! \nCould not find file " << path_c << "\n";
		return std::string("");
	}

	std::string XMLstring((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());

	fileStream.close();

	return XMLstring;
}

void GameMap::loadTmxMap(std::string path)
{
	std::string xmlString = loadXMLString(path);

	if (xmlString == "") return;

	char* xml = new char[xmlString.length() + 1];
	strcpy_s(xml, xmlString.length() + 1, xmlString.c_str());

	map.LoadFromXml(xml);
}

void GameMap::loadTileSets(SDL_Renderer* renderHandle, std::vector<TmxMapTileset>& tilesets)
{
	for (TmxMapTileset tileset : tilesets)
	{
		TileSet* newset = new TileSet;
		newset->SetName(tileset.mName);
		newset->SetfirstId(tileset.mFirstGid);

		newset->LoadTileSetFromFile(
			renderHandle, 
			paths::PathTilesets() + tileset.mName + ".png", 
			tileset.mTileWidth, 
			tileset.mTileHeight);

		tileSetFirstIdLookup.push_back(newset->GetFirstId());
		tileSets.push_back(newset);

	}
}

//Find the corresponding tileset to the key
int GameMap::findTilesetIndex(int key)
{
	int index = 0;
	for (int i = tileSets.size() - 1; i > 0; i--)
	{
		if (key + 1 > tileSets[i]->GetFirstId()) {
			index = i;
			break;
		}
	}
	return index;
}
