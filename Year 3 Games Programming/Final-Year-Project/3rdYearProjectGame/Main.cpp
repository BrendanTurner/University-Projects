#pragma once
#include <SFML\Graphics.hpp>
#include "Engine.h"
#include "Game.h"
#include "defines.h"

int main()
{
	Engine engine;
	if (!engine.initilizeWindow(screenWidth, screenHeight, "3rd Year Project Game")) return-1;
	Game game;
	
	engine.runEngine(game);
	
	return 0;
}