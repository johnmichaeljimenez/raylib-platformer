#ifndef _collision_h
#define _collision_h

typedef struct Wall
{
	Vector2 From;
	Vector2 To;
	float Length;
	Vector2 Normal;
	Vector2 Midpoint;
} Wall;

Wall CreateWall(Vector2 from, Vector2 to);
void LoadWalls();
void DrawWalls();
Vector2 GetClosestPoint(Vector2 p1, Vector2 p2, Vector2 pos);
bool CollideBody(Vector2 *pos, float radius);

#endif