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

const int wallCount = 2;
Wall Walls[2];

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

void LoadWalls()
{
	Walls[0] = CreateWall((Vector2){300, 100}, (Vector2){-300, 100});
	Walls[1] = CreateWall((Vector2){300, -200}, (Vector2){300, 100});
}

void DrawWalls()
{
	for (int i = 0; i < wallCount; i++)
	{
		DrawLineV(Walls[i].From, Walls[i].To, RAYWHITE);
		DrawLineV(Walls[i].Midpoint, Vector2Add(Walls[i].Midpoint, Vector2Multiply(Walls[i].Normal, (Vector2){12, 12})), RAYWHITE);
	}
}

Vector2 GetClosestPoint(Vector2 p1, Vector2 p2, Vector2 pos)
{
	Vector2 ap = Vector2Subtract(pos, p1);
	Vector2 ab = Vector2Subtract(p2, p1);

	float m = Vector2LengthSqr(ab);
	float d = Vector2DotProduct(ap, ab);

	float dist = d / m;
	if (dist < 0)
		return p1;
	if (dist > 1)
		return p2;

	Vector2 res = {};
	res.x = p1.x + ab.x * dist;
	res.y = p1.y + ab.y * dist;
	return res;
}

void CollideBody(Vector2 *pos, float radius)
{
	Vector2 curPos = {pos->x, pos->y};
	curPos.x = 0;

	for (int i = 0; i < wallCount; i++)
	{
		Wall w = Walls[i];
		Vector2 d = Vector2Subtract(w.To, w.Midpoint);

		// bool visible = Vector2DotProduct(w.Normal, d) > 0;
		// if (!visible)
		// 	continue;

		Vector2 c = GetClosestPoint(w.From, w.To, curPos);
		Vector2 cv = Vector2Subtract(c, curPos);
		float cd = Vector2Length(cv);

		if (cd <= radius)
		{
			float rd = cd - radius;
			curPos = Vector2Add(curPos, Vector2Multiply(Vector2Normalize(cv), (Vector2){rd, rd}));

			pos->x = curPos.x;
			pos->y = curPos.y;
		}
	}
}