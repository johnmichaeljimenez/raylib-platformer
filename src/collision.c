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



const int wallCount = 1;
Wall Walls[1];

void LoadWalls()
{
	Walls[0] = CreateWall((Vector2){300,100}, (Vector2){-300,100});
}

void DrawWalls()
{
	for (int i = 0; i < wallCount; i++)
	{
		DrawLineV(Walls[i].From, Walls[i].To, RAYWHITE);
		DrawLineV(Walls[i].Midpoint, Vector2Add(Walls[i].Midpoint, Vector2Multiply(Walls[i].Normal, (Vector2){12, 12})), RAYWHITE);
	}
}