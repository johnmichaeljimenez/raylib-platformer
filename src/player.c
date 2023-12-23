#include <raylib.h>

typedef struct
{
	Vector2 Position;
	Vector2 Size;
} Player;

void InitPlayer(Player* p)
{
	p->Position = (Vector2){0, 0};
}

void UpdatePlayer(Player* p)
{
	if (IsKeyDown(KEY_A))
		p->Position.x -= 100 * GetFrameTime();
	if (IsKeyDown(KEY_D))
		p->Position.x += 100 * GetFrameTime();
}

void DrawPlayer(Player* p)
{
	DrawRectangleV(p->Position, p->Size, RED);
}