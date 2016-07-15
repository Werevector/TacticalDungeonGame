#pragma once
#include "Actor.h"
#include "SpriteSet.h"
#include "sdl.h"
#include "ResourcePaths.h"
#include "Camera.h"
#include "Utils.h"

class IsoSpriteRenderComponent : public ActorComponent {
	
	friend class ActorFactory;

public:

	IsoSpriteRenderComponent();
	IsoSpriteRenderComponent(SDL_Renderer* renderHandle);
	
	void Init() override;
	void PostInit() override;

	void SetSpriteSheetName(std::string sheetName, std::string imgtype);
	
	void Update(float framedelta) override;
	
	void SetPos(float, float);
	void SetKey(int);
	
	void SetCamera(Camera* c);

protected:



private:

	

	SDL_Renderer*	mRenderHandle;
	SDL_Rect*		mRenderTarget;
	SpriteSet		mSpriteSet;

	Camera* mCameraPtr;

	float mPosX;
	float mPosY;

	int mSpriteKey;

	std::string mImagePath;
	std::string mMetaPath;


};