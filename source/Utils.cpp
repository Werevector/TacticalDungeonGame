#include "Utils.h"
using namespace utility;
Point2d utility::OrthoToIso(float orthoX, float orthoY)
{
	Point2d point;

	float isoX = (orthoY - orthoX) * (64 / 2);
	float isoY = ((orthoY + orthoX) * (32 / 2));

	point.x = isoX;
	point.y = isoY;

	return point;
}

Point2d utility::OrthoToIso(Point2d ortho)
{
	Point2d iso;
	iso.x = (ortho.x - ortho.y) * (64 / 2);
	iso.y = (ortho.x + ortho.y) * (32 / 2);
	return iso;
}

Point2d utility::OrthoToIsoOnMap(float orthoX, float orthoY, int layer, GameMap & map)
{
	Point2d point;

	float isoX = (orthoY - orthoX) * (map.GetMapTileWidth() / 2);
	float isoY = ((orthoY + orthoX) * (map.GetMapTileHeight() / 2)) + map.GetLayerOffset(layer);

	point.x = isoX;
	point.y = isoY;

	return point;
}
