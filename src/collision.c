#include <raylib.h>
#include <raymath.h>

typedef struct
{
	Vector2 From;
	Vector2 To;
	float Length;
	Vector2 Normal;
	Vector2 Midpoint;
} Wall;

Wall CreateWall(Vector2 from, Vector2 to)
{
	Wall w = {.From = from, .To = to};

	Vector2 diff = Vector2Subtract(to, from);
	w.Normal = Vector2Normalize((Vector2){-diff.y, diff.x});
	w.Length = Vector2Length(diff);
	w.Midpoint = Vector2Add(from, to);
	w.Midpoint.x /= 2;
	w.Midpoint.y /= 2;

	return w;
}