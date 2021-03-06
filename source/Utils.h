#pragma once
#include "GameMap.h"



namespace utility {

	class Point2d {
	public:
		Point2d() { x = 0; y = 0; }
		Point2d(float nX, float nY) : x(nX), y(nY) {}
		float x;
		float y;
	};

	Point2d OrthoToIso(float orthoX, float orthoY);
	Point2d OrthoToIso(Point2d ortho);
	Point2d OrthoToIsoOnMap(float orthoX, float orthoY, int layer, GameMap& map);

	Point2d IsoToOrtho(Point2d iso);

	int PositionTo1D(Point2d pos, int width);
	Point2d IndexToPosition(int index, int width, int height);

	int FindLowestValueIndex(std::vector<int> myarr);
}

	
