#include <raylib.h>
#ifndef AABB
#define AABB


typedef struct Bounds
{
	Vector2 position;
	Vector2 size;
	Vector2 min;
	Vector2 max;
} Bounds;


void InitAABB();
void UpdateAABB();
void DrawAABB();
void UpdateAABBData(Bounds* block);

#endif