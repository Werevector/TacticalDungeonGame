#include "ResourcePaths.h"

std::string paths::BasePath()
{
	return std::string("..\\..\\..\\resources\\");
}

std::string paths::PathActors()
{
	return  BasePath() + "actors\\";;
}

std::string paths::PathMaps()
{
	return BasePath() + "tmx_maps\\";
}

std::string paths::PathTilesets()
{
	return BasePath() + "tilesets\\";
}

std::string paths::PathSpriteSheets()
{
	return BasePath() + "spritesheets\\";
}
