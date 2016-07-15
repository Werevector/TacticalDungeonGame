#include "IsoSpriteRenderComponent.h"

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
	mSpriteSet.RenderSpriteFromKey(mRenderHandle, mPosX, mPosY, mSpriteKey);
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
