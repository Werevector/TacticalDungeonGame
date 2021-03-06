#include "TileSet.h"

TileSet::TileSet(std::string n, int first)
{
	name = n;
	firstId = first;
}

TileSet::~TileSet()
{
	textureSheet.FreeTexture();
}

bool TileSet::LoadTileSetFromFile(SDL_Renderer* renderer, std::string path, int tileWidthPx, int tileHeightPx)
{
	bool success = true;

	if (textureSheet.LoadFromImgFile(renderer, path))
	{
		tileWidth = tileWidthPx;
		tileHeight = tileHeightPx;

		tileNrX = textureSheet.getWidth() / tileWidth;
		tileNrY = textureSheet.getHeight() / tileHeight;

		for (int y = 0; y < tileNrY; y++)
		{
			for (int x = 0; x < tileNrX; x++)
			{
				SDL_Rect* clip = new SDL_Rect;
				clip->x = x * tileWidthPx;
				clip->y = y * tileHeightPx;
				clip->w = tileWidthPx;
				clip->h = tileHeightPx;
				sheetClips.push_back(clip);
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
		NULL,
		NULL,
		flip
		);
}
