#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>
#include "game.h"
#include "bullets.h"

int main()
{
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(1600, 900, "Raylib Platformer");

	InitGame();
	InitBulletSystem();

	while (!WindowShouldClose())
	{
		UpdateGame();
		UpdateBullets();

		if (IsKeyPressed(KEY_R))
		{
			BulletSpawn();
		}

		BeginDrawing();
		ClearBackground(DARKGRAY);
		RenderGame();
		DrawBullets();
		DrawFPS(12, 12);
		EndDrawing();
	}

	EndBulletSystem();
	CloseWindow();
}