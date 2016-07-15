#include "SpriteSet.h"

SpriteSet::SpriteSet()
{
}

SpriteSet::~SpriteSet()
{
}

bool SpriteSet::LoadSpriteSetFromFile(SDL_Renderer * renderHandle, std::string imagePath, std::string metaPath)
{
	bool success = true;

	success = spriteSheet.LoadFromImgFile(renderHandle, imagePath);
	if (success) {
		mWidthPx = spriteSheet.getWidth();
		mHeightPx = spriteSheet.getHeight();
		
		success = GenerateClipsFromMeta(metaPath);

	}
	else {

		success = false;
	}

	return success;
}

void SpriteSet::RenderSpriteFromKey(SDL_Renderer* renderHandle, int x, int y, int key, bool center)
{
	int cKey = 0;
	if (key < spriteClips.size()) cKey = key;
	
	SDL_Rect* clip = &spriteClips[cKey];
	SDL_Rect* target = new SDL_Rect();
	target->x = x;
	target->y = y;
	target->w = clip->w;
	target->h = clip->h;

	if (center)
	{
		x -= clip->w / 2;
		y -= clip->h / 2;
	}

	//SDL_RenderDrawRect(renderHandle, target);
	spriteSheet.RenderTexture(renderHandle, x, y, clip, target, NULL, NULL, SDL_FLIP_NONE);
}

int SpriteSet::GetAmountOfClips()
{
	return spriteClips.size();
}

bool SpriteSet::GenerateClipsFromMeta(std::string metaPath)
{
	using namespace std;
	bool success = true;
	
	fstream metaStream(metaPath);

	if (metaStream.is_open()) {

		int x, y, w, h;


		while (metaStream >> x >> y >> w >> h) {
			SDL_Rect spriteRect;
			spriteRect.x = x;
			spriteRect.y = y;
			spriteRect.w = w;
			spriteRect.h = h;

			spriteClips.push_back(spriteRect);

		}

	}
	else {
		cout << "Could not open metafile:\n " << metaPath << endl;
	}

	return success;
}
