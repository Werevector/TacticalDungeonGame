#include "IsoSpriteRenderComponent.h"
using namespace utility;

IsoSpriteRenderComponent::IsoSpriteRenderComponent()
{
	mSpriteKey = 0;
}

void IsoSpriteRenderComponent::Init()
{
}

void IsoSpriteRenderComponent::PostInit()
{
	mSpriteSet.LoadSpriteSetFromFile(mRenderHandle, mImagePath, mMetaPath);
}

IsoSpriteRenderComponent::IsoSpriteRenderComponent(SDL_Renderer * renderHandle)
{
	mRenderHandle = renderHandle;
}

void IsoSpriteRenderComponent::SetSpriteSheetName(std::string sheetName, std::string imgtype)
{
	mImagePath = paths::PathSpriteSheets() + sheetName + imgtype;
	mMetaPath = paths::PathSpriteSheets() + sheetName + ".meta";
}

void IsoSpriteRenderComponent::Update(float framedelta)
{
	//Convert map coordinates to isometric for rendering
	Point2d iso = OrthoToIso(Point2d(mPosX, mPosY));
	iso.x -= mCameraPtr->mPositionX;
	iso.y -= mCameraPtr->mPositionY;

	mSpriteSet.RenderSpriteFromKey(mRenderHandle, iso.x, iso.y, mSpriteKey, true);
}

void IsoSpriteRenderComponent::SetPos(float x, float y) 
{
	mPosX = x;
	mPosY = y;
}

void IsoSpriteRenderComponent::SetKey(int newKey)
{
	mSpriteKey = newKey;
}

void IsoSpriteRenderComponent::SetCamera(Camera * c)
{
	mCameraPtr = c;
}
