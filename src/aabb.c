#include <raylib.h>
#include <raymath.h>
#include "aabb.h"
#include "time.h"

static Bounds p;
static Bounds block;
static bool colliding;

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
	return a->min.x <= b->max.x &&
		a->max.x >= b->min.x &&
		a->min.y <= b->max.y &&
		a->max.y >= b->min.y;
}

void UpdateAABB()
{
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
}
