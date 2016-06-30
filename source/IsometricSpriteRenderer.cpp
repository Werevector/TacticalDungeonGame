#include "IsometricSpriteRenderer.h"

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

void IsometricSpriteRenderer::Update(int framedelta)
{
	mSpriteSet.RenderSpriteFromKey(mRenderHandle, mPosX, mPosY, 0);
}

void IsometricSpriteRenderer::SetPos(int x, int y) 
{
	mPosX = x;
	mPosY = y;
}
