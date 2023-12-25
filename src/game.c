#include "time.h"
#include <raylib.h>
#include "game.h"
#include "collision.h"
#include "player.h"
#include <raymath.h>
#include "bullets.h"
#include "aabb.h"

Camera2D camera;
static Vector2 cameraLerpPos;

Player player;

static void setupCamera()
{
	camera.target = (Vector2){ 0, 0 };
	camera.zoom = 1;
	camera.offset = (Vector2){ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
}

void InitGame()
{
	setupCamera();
	PlayerInit(&player);
	InitBulletSystem();
	LoadWalls();
	InitAABB();
}

void UpdateGame()
{
	PlayerUpdate(&player);
	UpdateBullets();

	cameraLerpPos.x = player.Position.x;
	camera.target.x = Lerp(camera.target.x, cameraLerpPos.x, TICKRATE);
}

void RenderGame()
{
	BeginMode2D(camera);

	DrawWalls();
	DrawAABB();
	PlayerDraw(&player);
	DrawBullets();

	EndMode2D();
}

void EndGame()
{
	EndBulletSystem();
}

int n = 0;
void RunLoop()
{
	float previous = GetTime();
	float lag = 0.0;

	while (!WindowShouldClose() && n < 99999)
	{
		n++;
		float current = GetTime();
		float elapsed = current - previous;
		previous = current;
		lag += elapsed;

		while (lag >= TICKRATE)
		{
			UpdateGame();
			lag -= TICKRATE;
		}

		//draw

		BeginDrawing();
		ClearBackground(DARKGRAY);
		RenderGame();
		DrawFPS(12, 12);
		EndDrawing();

		n = 0;
	}
}