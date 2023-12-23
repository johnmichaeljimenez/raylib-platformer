#include <raylib.h>

typedef struct
{
	Vector2 Position;
	Vector2 Size;
	Vector2 HalfSize;

	float MovementSpeed;
} Player;

void InitPlayer(Player *p)
{
	p->HalfSize = (Vector2){p->Size.x / 2, p->Size.y / 2};
	p->Position = (Vector2){0, 0};
}

void UpdatePlayer(Player *p)
{
	// Vector2 lastPos = p->Position;

	if (IsKeyDown(KEY_A))
		p->Position.x -= p->MovementSpeed * GetFrameTime();
	if (IsKeyDown(KEY_D))
		p->Position.x += p->MovementSpeed * GetFrameTime();
	if (IsKeyDown(KEY_W))
		p->Position.y -= p->MovementSpeed * GetFrameTime();
	if (IsKeyDown(KEY_S))
		p->Position.y += p->MovementSpeed * GetFrameTime();

	// collision here
	CollideBody(&(p->Position), 32);
}

void DrawPlayer(Player *p)
{
	// DrawRectangleV(p->Position, p->Size, RED);
	DrawCircleV(p->Position, 32, RED);
}