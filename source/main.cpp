#pragma once
#include "sdl.h"
#include <iostream>
#include "GameLogic.h"

int main(int argc, char* argv[])
{

	GameLogic game;
	game.InitTestVersion();
	game.Run();
	return 0;
}