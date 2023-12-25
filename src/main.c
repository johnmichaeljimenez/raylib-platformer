#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>
#include "game.h"

int main()
{
	SetConfigFlags(FLAG_VSYNC_HINT);// | FLAG_WINDOW_MAXIMIZED | FLAG_WINDOW_UNDECORATED);
	InitWindow(1600, 900, "Raylib Platformer");
	//SetTargetFPS(200);

	InitGame();
	RunLoop();
	EndGame();
	CloseWindow();
}