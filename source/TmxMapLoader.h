#pragma once
#include <string>
#include <vector>

class TmxMapTileset {
public:
	int mFirstGid;
	int mTileWidth;
	int mTileHeight;
	std::string mName;
	std::string mFilename;
};

class TmxMapLayer {
public:
	TmxMapLayer();
	std::string mName;
	int mWidth;
	int mHeight;
	int mOffsetx;
	int mOffsety;
	std::vector<int> mData;
};

class TmxMap {
public:

	TmxMap();
	TmxMap(char *xml);
	void LoadFromXml(char *xml);

	int mWidth;
	int mHeight;
	int mTileWidth;
	int mTileHeight;

	std::vector<TmxMapTileset>  mTilesets;
	std::vector<TmxMapLayer>	mLayers;

};