#pragma once
#include "sdl.h"
#include <iostream>
class SDLGameWindow {

public:

	bool Init();
	bool CreateGameWindowAndRenderer();
	void versionPrint();
	void Clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void Clear();
	void SwapBuffer();

	SDL_Rect windowMetrics;
	Uint32 flags;
	std::string windowTitle;
	SDL_Window* windowHandle;
	SDL_Renderer* renderHandle;
	

};