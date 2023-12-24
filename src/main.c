#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>
#include "game.h"

int main()
{
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(1600, 900, "Raylib Platformer");

	InitGame();

	while (!WindowShouldClose())
	{
		UpdateGame();

		BeginDrawing();
		ClearBackground(DARKGRAY);
		RenderGame();
		DrawFPS(12, 12);
		EndDrawing();
	}

	EndGame();
	CloseWindow();
}