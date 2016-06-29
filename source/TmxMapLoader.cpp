#define _CRT_SECURE_NO_WARNINGS
#include "TmxMapLoader.h"
#include "rapidxml.hpp"
#include <iostream>
#include <sstream>

TmxMapLayer::TmxMapLayer() {
	mWidth		= 0;
	mHeight		= 0;
	mOffsetx	= 0;
	mOffsety	= 0;
}

TmxMap::TmxMap() {
	mWidth		= 0;
	mHeight		= 0;
	mTileWidth	= 0;
	mTileHeight = 0;
}

TmxMap::TmxMap(char * xml)
{
	mWidth		= 0;
	mHeight		= 0;
	mTileWidth	= 0;
	mTileHeight = 0;

	LoadFromXml(xml);
}

void TmxMap::LoadFromXml(char * xml)
{
	using namespace rapidxml;

	xml_document<> doc;
	doc.parse<0>(xml);

	xml_node<> *mapNode = doc.first_node("map");
	mWidth = atoi(mapNode->first_attribute("width")->value());
	mHeight = atoi(mapNode->first_attribute("height")->value());
	mTileWidth = atoi(mapNode->first_attribute("tilewidth")->value());
	mTileHeight = atoi(mapNode->first_attribute("tileheight")->value());

	
	xml_node<> *tilesetNode = mapNode->first_node("tileset");
	while(tilesetNode) 
	{
		TmxMapTileset tileset;
		tileset.mFirstGid = atoi(tilesetNode->first_attribute("firstgid")->value());
		tileset.mName = tilesetNode->first_attribute("name")->value();
		tileset.mFilename = tilesetNode->first_node("image")->first_attribute("source")->value();
		tileset.mTileWidth = atoi(tilesetNode->first_attribute("tilewidth")->value());
		tileset.mTileHeight = atoi(tilesetNode->first_attribute("tileheight")->value());

		mTilesets.push_back(tileset);
		tilesetNode = tilesetNode->next_sibling("tileset");
	}

	xml_node<> *layerNode = mapNode->first_node("layer");
	while (layerNode) 
	{
		TmxMapLayer layer;
		layer.mName = layerNode->first_attribute("name")->value();
		layer.mWidth = atoi(layerNode->first_attribute("width")->value());
		layer.mHeight = atoi(layerNode->first_attribute("height")->value());

		//The Tiled editor does not write the offset attribute when offset = 0.
		//Therefore we do a NULL check on the node
		auto offsetxNode = layerNode->first_attribute("offsetx");
		if (offsetxNode) layer.mOffsetx = atoi(offsetxNode->value());

		auto offsetyNode = layerNode->first_attribute("offsety");
		if (offsetyNode) layer.mOffsety = atoi(offsetyNode->value());

		std::string dataString(layerNode->first_node("data")->value());

		std::istringstream stringStream(dataString);
		std::string token;

		while (std::getline(stringStream, token, ',')) {
			layer.mData.push_back(atoi(token.c_str()));
		}

		mLayers.push_back(layer);
		layerNode = layerNode->next_sibling("layer");

	}


	

}
