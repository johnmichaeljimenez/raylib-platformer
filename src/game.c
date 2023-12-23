#include <raylib.h>

#include "src/player.c"
#include "src/collision.c"

#define DELTA GetFrameTime()

Camera2D camera = {};
static Vector2 cameraLerpPos;

Player player = {
	.Size = (Vector2){64, 96},
	.Bounds = {.Size = {64, 96}},
	.MovementSpeed = 200
	};

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
	camera.target.x = Lerp(camera.target.x, cameraLerpPos.x, DELTA);
}

void RenderGame()
{
	BeginMode2D(camera);

	DrawWalls();
	DrawPlayer(&player);
	
	EndMode2D();
}