#pragma once
#include "GameMap.h"



namespace utility {

	struct Point2d {
		float x;
		float y;
	};

	Point2d OrthoToIso(float orthoX, float orthoY);
	Point2d OrthoToIso(Point2d ortho);

	Point2d OrthoToIsoOnMap(float orthoX, float orthoY, int layer, GameMap& map);
}

	
