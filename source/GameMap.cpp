#include "GameMap.h"

bool GameMap::LoadMapFromTmx(SDL_Renderer* renderHandle, std::string path)
{
	bool success = true;

	NLTmxMap* map = loadTmxMap(path);

	mapWidth = map->width;
	mapHeight = map->height;

	NrOfTilesInLayer = mapWidth * mapHeight;

	tileWidth = map->tileWidth;
	tileHeight = map->tileHeight;

	mapWidthPx = mapWidth * tileWidth;
	mapHeightPx = mapHeight * tileHeight;

	NrOfLayers = map->layers.size();

	loadTileSets(renderHandle, map->tilesets);

	delete map;

	return success;
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

	char*  xml = new char[xmlString.length() + 1];
	strcpy_s(xml, xmlString.length() + 1, xmlString.c_str());

	NLTmxMap* map = NLLoadTmxMap(xml);
	
	return map;
}

std::vector<TileSet> GameMap::loadTileSets(SDL_Renderer* renderHandle, std::vector<NLTmxMapTileset*> tilesets)
{
	std::vector<TileSet> tilesetCollection;

	
	for (NLTmxMapTileset* tileset : tilesets)
	{
		TileSet newset;
		newset.SetName(tileset->name);
		newset.SetfirstId(tileset->firstGid);

		/*newset.LoadTileSetFromFile(
			renderHandle, 
			paths::pathTilesets + tileset->name + ".png", 
			tileset->tileWidth, 
			tileset->tileHeight,
			);*/

	}

	return tilesetCollection;
}
