#include <raylib.h>

#include "src/player.c"

Camera2D camera = {};
Player player = {
	.Size = (Vector2){
		64, 96
	}
};

static void setupCamera()
{
	camera.target = (Vector2){0, 0};
	camera.zoom = 1;
	camera.offset = (Vector2){ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
}

void InitGame()
{
	setupCamera();
	InitPlayer(&player);
}

void UpdateGame()
{
	UpdatePlayer(&player);

	camera.target.x = player.Position.x;
}

void RenderGame()
{
	BeginMode2D(camera);

	DrawRectangle(-100, 12, 300, 200, GREEN);

	DrawPlayer(&player);
	EndMode2D();
}