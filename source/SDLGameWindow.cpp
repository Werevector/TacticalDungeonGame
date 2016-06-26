#include "SDLGameWindow.h"

bool SDLGameWindow::Init()
{
	windowTitle = "ActorSystem";
	windowMetrics.x = 100;
	windowMetrics.y = 100;
	windowMetrics.w = 1920 / 2;
	windowMetrics.h = 1080 / 2;
	flags = SDL_WINDOW_SHOWN;

	bool success = true;
	SDL_Init(SDL_INIT_EVERYTHING);
	return success;
}

bool SDLGameWindow::CreateGameWindowAndRenderer()
{
	windowHandle =
		SDL_CreateWindow(windowTitle.c_str(),
			windowMetrics.x,
			windowMetrics.y,
			windowMetrics.w,
			windowMetrics.h,
			flags);

	renderHandle = SDL_CreateRenderer(windowHandle, -1, SDL_RENDERER_ACCELERATED);
	return true;
}

void SDLGameWindow::Clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	SDL_SetRenderDrawColor(renderHandle, r, g, b, a);
	SDL_RenderClear(renderHandle);
}

void SDLGameWindow::Clear() {
	SDL_SetRenderDrawColor(renderHandle, 0X33, 0X33, 0X33, 0XFF);
	SDL_RenderClear(renderHandle);
}

void SDLGameWindow::SwapBuffer()
{
	SDL_RenderPresent(renderHandle);
}

void SDLGameWindow::versionPrint()
{
	SDL_version compiled;
	SDL_version linked;

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("But we are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}