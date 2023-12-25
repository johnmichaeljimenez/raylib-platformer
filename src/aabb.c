#include <raylib.h>
#include <raymath.h>
#include "aabb.h"
#include "time.h"
#include "stdio.h"

int BlockListCount = 3;
Bounds BlockList[3];

void InitAABB()
{
	BlockList[0] = CreateBounds((Vector2) { 0, 80 }, (Vector2) { 300, 30 });
	BlockList[1] = CreateBounds((Vector2) { 200, 0 }, (Vector2) { 120, 150 });
	BlockList[2] = CreateBounds((Vector2) { -200, 0 }, (Vector2) { 120, 150 });
}

Bounds CreateBounds(Vector2 pos, Vector2 size)
{
	Bounds b = (Bounds){ 0 };

	b.position = pos;
	b.size = size;

	UpdateAABBData(&b);

	return b;
}

bool MoveAABB(Bounds* a, Vector2* pos)
{
	for (int i = 0; i < BlockListCount; i++)
	{
		Bounds b = BlockList[i];
		if (IsAABBColliding(a, &b))
		{
			Vector2 diff = Vector2Subtract(a->position, b.position);
			diff.x = diff.x >= 0 ? 1 : -1;
			diff.y = diff.y >= 0 ? 1 : -1;

			Rectangle colRect = GetCollisionRec((Rectangle) { a->min.x, a->min.y, a->size.x, a->size.y }, (Rectangle) { b.min.x, b.min.y, b.size.x, b.size.y });

			if (colRect.height > 0 && colRect.width > 0)
			{
				if (colRect.width > colRect.height)
				{
					a->position.y += diff.y * colRect.height;
				}
				else {
					a->position.x += diff.x * colRect.width;
				}

				UpdateAABBData(a);
			}
		}
	}

	pos->x = a->position.x;
	pos->y = a->position.y;
}

bool IsAABBColliding(Bounds* a, Bounds* b)
{
	bool c = a->min.x <= b->max.x &&
		a->max.x >= b->min.x &&
		a->min.y <= b->max.y &&
		a->max.y >= b->min.y;

	return c;
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
	for (int i = 0; i < BlockListCount; i++)
	{
		Bounds b = BlockList[i];

		DrawBounds(&b, BLUE, false);
	}
}

void DrawBounds(Bounds* b, Color c, bool solid)
{
	if (solid)
		DrawRectangle(b->min.x, b->min.y, b->size.x, b->size.y, c);
	else
		DrawRectangleLines(b->min.x, b->min.y, b->size.x, b->size.y, c);
}