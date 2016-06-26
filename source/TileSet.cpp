#include "TileSet.h"

TileSet::TileSet(std::string n, int first)
{
	name = n;
	firstId = first;
}

TileSet::~TileSet()
{
	for (SDL_Rect* r : sheetClips) {
		delete r;
	}
	textureSheet.FreeTexture();
}

bool TileSet::LoadTileSetFromFile(SDL_Renderer* renderer, std::string path, int tileWidthPx, int tileHeightPx, int tileNrX, int tileNrY)
{
	bool success = true;

	if (textureSheet.LoadFromImgFile(renderer, path))
	{
		tileWidth = tileWidthPx;
		tileHeight = tileHeightPx;

		for (int y = 0; y < tileNrY; y++)
		{
			for (int x = 0; x < tileNrX; x++)
			{
				SDL_Rect* clip = new SDL_Rect;
				clip->x = x * tileWidthPx;
				clip->y = y * tileHeightPx;
				clip->w = tileWidthPx;
				clip->h = tileHeightPx;
			}
		}
	}
	else {
		success = false;
	}

	return success;
}

//Metadata version (TODO)
bool TileSet::LoadTileSetFromFile(SDL_Renderer * renderer, std::string path, std::string metaDataPath)
{
	bool success = true;


	/*if (textureSheet.LoadFromImgFile(renderer, path)) {
		sheetClips = MetaFileReader::readSpriteMetaPositions(metapath);
		if (sheetRectangles.size() == 0) {
			success = false;
		}
	}
	else {
		success = false;
	}*/

	return success;
}

void TileSet::RenderFromSheet(SDL_Renderer * renderer, int x, int y, int key, SDL_Rect * target, double angle, SDL_RendererFlip flip)
{
	SDL_Rect* clip = sheetClips[key];

	textureSheet.RenderTexture(
		renderer,
		x,
		y,
		clip,
		target,
		angle,
		NULL,
		flip
		);
}
