#include <raylib.h>

#include "src/collision.c"
#include "src/player.c"

Camera2D camera = {};
static Vector2 cameraLerpPos;

Player player = {};

static void setupCamera()
{
	camera.target = (Vector2){0, 0};
	camera.zoom = 1;
	camera.offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
}

void InitGame()
{
	setupCamera();
	InitPlayer(&player);
	LoadWalls();
}

void UpdateGame()
{
	UpdatePlayer(&player);

	cameraLerpPos.x = player.Position.x;
	camera.target.x = Lerp(camera.target.x, cameraLerpPos.x, GetFrameTime());
}

void RenderGame()
{
	BeginMode2D(camera);

	DrawWalls();
	DrawPlayer(&player);

	EndMode2D();
}