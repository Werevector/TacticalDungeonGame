#pragma once
#include "Actor.h"
#include "SpriteSet.h"
#include "sdl.h"
#include "ResourcePaths.h"

class IsometricSpriteRenderer : public ActorComponent {
	
	friend class ActorFactory;

public:

	IsometricSpriteRenderer();
	void Init() override;
	void PostInit() override;
	IsometricSpriteRenderer(SDL_Renderer* renderHandle);
	void SetSpriteSheetName(std::string sheetName, std::string imgtype);
	void Update(int framedelta) override;
	void SetPos(int, int);
	void SetKey(int);

protected:



private:
	SDL_Renderer*	mRenderHandle;
	SDL_Rect*		mRenderTarget;
	SpriteSet		mSpriteSet;

	int mPosX;
	int mPosY;

	int mSpriteKey;

	std::string mImagePath;
	std::string mMetaPath;

	
	

};