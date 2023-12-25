#include <raylib.h>
#include <raymath.h>
#include "aabb.h"
#include "time.h"

static Bounds p;
static Bounds block;
static bool colliding;
static bool isWall;
static float xd, yd;

static Rectangle rr;

void InitAABB()
{
	colliding = false;
	p = (Bounds){ 0 };
	block = (Bounds){ 0 };

	p.position.x = -100;
	p.position.y = -100;
	p.size.x = 64;
	p.size.y = 96;

	block.position.x = 0;
	block.position.y = 0;
	block.size.x = 300;
	block.size.y = 64;

	UpdateAABBData(&p);
	UpdateAABBData(&block);
}

static bool IsAABBColliding(Bounds* a, Bounds* b)
{
	bool c = a->min.x <= b->max.x &&
		a->max.x >= b->min.x &&
		a->min.y <= b->max.y &&
		a->max.y >= b->min.y;

	return c;
}

void UpdateAABB()
{
	Vector2 pos = p.position;

	if (IsKeyDown(KEY_UP))
		p.position.y -= 150 * TICKRATE;
	else if (IsKeyDown(KEY_DOWN))
		p.position.y += 150 * TICKRATE;
	if (IsKeyDown(KEY_LEFT))
		p.position.x -= 150 * TICKRATE;
	else if (IsKeyDown(KEY_RIGHT))
		p.position.x += 150 * TICKRATE;

	UpdateAABBData(&p);
	colliding = IsAABBColliding(&p, &block);

	if (colliding)
	{
		Vector2 diff = Vector2Subtract(p.position, block.position);
		diff.x = diff.x >= 0? 1 : -1;
		diff.y = diff.y >= 0 ? 1 : -1;

		rr = GetCollisionRec((Rectangle) { p.min.x, p.min.y, p.size.x, p.size.y }, (Rectangle) { block.min.x, block.min.y, block.size.x, block.size.y });

		if (rr.height > 0 && rr.width > 0)
		{
			if (rr.width > rr.height)
			{
				isWall = false;
				p.position.y += diff.y * rr.height;
			}
			else {
				isWall = true;
				p.position.x += diff.x * rr.width;
			}
		}
	}
}

void UpdateAABBData(Bounds* b)
{
	Vector2 half = b->size;
	half.x /= 2;
	half.y /= 2;

	b->min = Vector2Subtract(b->position, half);
	b->max = Vector2Add(b->position, half);
}

void DrawAABB()
{
	DrawRectangle(p.min.x, p.min.y, p.size.x, p.size.y, colliding ? RED : GREEN);
	DrawRectangle(block.min.x, block.min.y, block.size.x, block.size.y, BLUE);

	if (colliding)
		DrawRectangleRec(rr, WHITE);

	DrawText(colliding ? isWall ? "WALL" : "FLOOR" : "NONE", 12, 12, 20, RED);
}
