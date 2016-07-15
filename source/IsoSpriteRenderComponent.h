#pragma once
#include "Actor.h"
#include "SpriteSet.h"
#include "sdl.h"
#include "ResourcePaths.h"

class IsoSpriteRenderComponent : public ActorComponent {
	
	friend class ActorFactory;

public:

	IsoSpriteRenderComponent();
	void Init() override;
	void PostInit() override;
	IsoSpriteRenderComponent(SDL_Renderer* renderHandle);
	void SetSpriteSheetName(std::string sheetName, std::string imgtype);
	void Update(float framedelta) override;
	void SetPos(float, float);
	void SetKey(int);

protected:



private:
	SDL_Renderer*	mRenderHandle;
	SDL_Rect*		mRenderTarget;
	SpriteSet		mSpriteSet;

	float mPosX;
	float mPosY;

	int mSpriteKey;

	std::string mImagePath;
	std::string mMetaPath;

	
	

};