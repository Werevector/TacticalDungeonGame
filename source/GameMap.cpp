#include "GameMap.h"

bool GameMap::LoadMapFromTmx(SDL_Renderer* renderHandle, std::string path)
{
	bool success = true;

	map = loadTmxMap(path);

	NrOfTilesInLayer = map->width * map->height;

	mapWidthPx = map->width * map->tileWidth;
	mapHeightPx = map->height * map->tileHeight;

	NrOfLayers = map->layers.size();

	/*for (int i = 0; i < NrOfTilesInLayer; i++) 
	{
		std::cout << map->layers[0]->data[i];
		if ((i / map->width > 9))
		{
			std::cout << std::endl;
		}
	}*/

	loadTileSets(renderHandle, map->tilesets);

	//testTex.LoadFromImgFile(renderHandle, paths::PathTilesets() + "yes.PNG");
	testTex.LoadFromImgFile(renderHandle, paths::PathTilesets() + "iso-64x64-building_2" + ".png");
	return success;
}

void GameMap::RenderMap(SDL_Renderer* renderHandle)
{
	int key = 0;
	int tilesetIndex = 0;
	int x = 0;
	int y = 0;
	SDL_Rect target;
	target.x = 0;
	target.y = 0;
	target.w = 64;
	target.h = 64;

	SDL_Rect tes;
	tes.x = 0;
	tes.y = 0;
	tes.w = 500;
	tes.h = 500;

	SDL_Rect tar;
	tar.x = 0;
	tar.y = 0;
	tar.w = 500;
	tar.h = 500;

	for (int layer = 0; layer < map->layers.size(); layer++) 
	{
		for (int tile = 0; tile < NrOfTilesInLayer; tile++) 
		{
			//Only render if the tile exists (non zero)
			if (map->layers[layer]->data[tile] != 0) {
				key = map->layers[layer]->data[tile] - 1;

				//Needed because of the structure of the tilesets
				//when using multiple tilesets in the same map
				//should be reworked
				tilesetIndex = findTilesetIndex(key);
				if (tilesetIndex != 0) {
					key -= tileSets[tilesetIndex]->GetFirstId()-1;
				}
				

				//TODO:: - Rendering in the Texture class uses the target rectangle in a redundant way
				//       - A whole SDL_Rect is not required.
				//
				//		 - Tile dimensions are different for texture, and map tiles, this should be clearer

				int tx = tile / map->width;
				int ty = tile % map->height;

				//x = (tx - ty) * (map->tileWidth / 2);
				//y = (tx + ty) * (map->tileHeight / 2);

				x = (ty - tx) * (map->tileWidth / 2);
				y = (ty + tx) * (map->tileHeight / 2);
				//A hack to center the map
				x += mapWidthPx/2;
				y += 100;
				
				tileSets[tilesetIndex]->RenderFromSheet(renderHandle, x, y, key, &target, NULL, SDL_FLIP_NONE);

			}
			
		}
	}

}

std::string GameMap::loadXMLString(std::string path)
{
	const char* path_c = path.c_str();
	ifstream fileStream;
	fileStream.open(path_c);

	if (!fileStream.is_open()) {
		cout << "Roomloader failed ! \nCould not find file " << path_c << "\n";
		return std::string("");
	}

	std::string XMLstring((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());

	fileStream.close();

	return XMLstring;
}

NLTmxMap * GameMap::loadTmxMap(std::string path)
{
	//the pointer to the xml file
	std::string xmlString = loadXMLString(path);

	if (xmlString == "") return false;

	char* xml = new char[xmlString.length() + 1];
	strcpy_s(xml, xmlString.length() + 1, xmlString.c_str());

	NLTmxMap* map = NLLoadTmxMap(xml);
	
	return map;
}

void GameMap::loadTileSets(SDL_Renderer* renderHandle, std::vector<NLTmxMapTileset*> tilesets)
{
	for (NLTmxMapTileset* tileset : tilesets)
	{
		TileSet* newset = new TileSet;
		newset->SetName(tileset->name);
		newset->SetfirstId(tileset->firstGid);

		newset->LoadTileSetFromFile(
			renderHandle, 
			paths::PathTilesets() + tileset->name + ".png", 
			tileset->tileWidth, 
			tileset->tileHeight);

		tileSetFirstIdLookup.push_back(newset->GetFirstId());
		tileSets.push_back(newset);

	}
}

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
