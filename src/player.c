#include <raylib.h>
#include <src/bounds.c>

typedef struct
{
	Vector2 Position;
	Vector2 Size;
	Bounds Bounds;
	Vector2 HalfSize;

	float MovementSpeed;
} Player;

void InitPlayer(Player *p)
{
	p->HalfSize = (Vector2){p->Size.x / 2, p->Size.y / 2};
	p->Position = (Vector2){0, 0};
	p->Bounds = (Bounds){p->Position, p->Size};
}

void UpdatePlayer(Player *p)
{
	Vector2 lastPos = p->Position;

	if (IsKeyDown(KEY_A))
		p->Position.x -= p->MovementSpeed * GetFrameTime();
	if (IsKeyDown(KEY_D))
		p->Position.x += p->MovementSpeed * GetFrameTime();

	// collision here
	 if (p->Position.y + p->HalfSize.y >= 10)
	 	p->Position.y -= 10;
		
	 if (p->Position.x + p->HalfSize.x >= 500)
	 	p->Position.x -= 1;

	p->Bounds.Center = p->Position;
}

void DrawPlayer(Player *p)
{
	DrawRectangleV(p->Position, p->Size, RED);
}