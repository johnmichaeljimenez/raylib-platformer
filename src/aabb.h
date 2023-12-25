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


Bounds CreateBounds(Vector2 pos, Vector2 size);
void InitAABB();
void DrawAABB();
void UpdateAABBData(Bounds* block);
bool IsAABBColliding(Bounds* a, Bounds* b);
bool MoveAABB(Bounds* a, Vector2* pos);
void DrawBounds(Bounds* a, Color c);

#endif