#include <raylib.h>
#include <raymath.h>
#include "aabb.h"
#include "time.h"

int BlockListCount = 1;
Bounds BlockList[1];

void InitAABB()
{
	BlockList[0] = CreateBounds((Vector2) { 0, 80 }, (Vector2) { 300, 30 });
}

Bounds CreateBounds(Vector2 pos, Vector2 size)
{
	Bounds b = (Bounds){ 0 };

	b.position = pos;
	b.size = size;

	UpdateAABBData(&b);

	return b;
}

bool MoveAABB(Bounds* a)
{
	for (int i = 0; i < BlockListCount; i++)
	{
		Bounds b = BlockList[i];
		if (IsAABBColliding(&a, &b))
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
			}

			UpdateAABBData(a);
		}
	}
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

		DrawRectangleLines(b.min.x, b.min.y, b.size.x, b.size.y, BLUE);
	}
}
