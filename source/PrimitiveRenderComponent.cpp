#include "PrimitiveRenderComponent.h"

void PrimitiveRenderComponent::Update(int framedelta)
{
	SDL_SetRenderDrawColor(renderHandle, renderColor.r, renderColor.g, renderColor.b, renderColor.a);
	SDL_RenderFillRect(renderHandle, &renderTarget);
}