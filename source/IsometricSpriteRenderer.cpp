#include "IsometricSpriteRenderer.h"

IsometricSpriteRenderer::IsometricSpriteRenderer()
{
	mSpriteKey = 0;
}

void IsometricSpriteRenderer::Init()
{
}

void IsometricSpriteRenderer::PostInit()
{
	mSpriteSet.LoadSpriteSetFromFile(mRenderHandle, mImagePath, mMetaPath);
}

IsometricSpriteRenderer::IsometricSpriteRenderer(SDL_Renderer * renderHandle)
{
	mRenderHandle = renderHandle;
}

void IsometricSpriteRenderer::SetSpriteSheetName(std::string sheetName, std::string imgtype)
{
	mImagePath = paths::PathSpriteSheets() + sheetName + imgtype;
	mMetaPath = paths::PathSpriteSheets() + sheetName + ".meta";
}

void IsometricSpriteRenderer::Update(float framedelta)
{
	mSpriteSet.RenderSpriteFromKey(mRenderHandle, mPosX, mPosY, mSpriteKey);
}

void IsometricSpriteRenderer::SetPos(float x, float y) 
{
	mPosX = x;
	mPosY = y;
}

void IsometricSpriteRenderer::SetKey(int newKey)
{
		mSpriteKey = newKey;
}
