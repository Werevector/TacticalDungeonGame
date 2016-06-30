#pragma once
#include "ActorComponent.h"
#include "SpriteSet.h"
#include "sdl.h"
#include "ResourcePaths.h"

class IsometricSpriteRenderer : public ActorComponent {
	
	friend class ActorFactory;

public:

	void PostInit() override;
	IsometricSpriteRenderer(SDL_Renderer* renderHandle);
	void SetSpriteSheetName(std::string sheetName, std::string imgtype);
	void Update(int framedelta) override;
	void SetPos(int, int);

protected:



private:
	SDL_Renderer*	mRenderHandle;
	SDL_Rect*		mRenderTarget;
	SpriteSet		mSpriteSet;

	int mPosX;
	int mPosY;

	std::string mImagePath;
	std::string mMetaPath;
	

};