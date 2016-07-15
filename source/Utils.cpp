#include "Utils.h"

Point2d OrthoToIso(float orthoX, float orthoY)
{
	Point2d point;

	float isoX = (orthoY - orthoX) * (64 / 2);
	float isoY = ((orthoY + orthoX) * (32 / 2));

	point.x = isoX;
	point.y = isoY;

	return point;
}

Point2d OrthoToIsoOnMap(float orthoX, float orthoY, int layer, GameMap& map)
{
	Point2d point;

	float isoX = (orthoY - orthoX) * (map.GetMapTileWidth() / 2);
	float isoY = ((orthoY + orthoX) * (map.GetMapTileHeight() / 2)) + map.GetLayerOffset(layer);

	point.x = isoX;
	point.y = isoY;

	return point;
}