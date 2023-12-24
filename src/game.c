#include <raylib.h>
#include "game.h"
#include "collision.h"
#include "player.h"
#include <raymath.h>

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
	LoadWalls();
}

void UpdateGame()
{
	PlayerUpdate(&player);

	cameraLerpPos.x = player.Position.x;
	camera.target.x = Lerp(camera.target.x, cameraLerpPos.x, GetFrameTime());
}

void RenderGame()
{
	BeginMode2D(camera);

	DrawWalls();
	PlayerDraw(&player);

	EndMode2D();
}