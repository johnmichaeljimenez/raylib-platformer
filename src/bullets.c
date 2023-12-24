#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <stdio.h>
#include "bullets.h"

int bulletIndex;
int bulletCount;
Bullet* bulletsArray;

void BulletSpawn()
{
	for (int i = 0; i < bulletCount; i++)
	{
		if (!bulletsArray[i].Alive)
		{
			bulletIndex = i;
			break;
		}
	}

	Bullet b = bulletsArray[bulletIndex];
	b.Alive = true;
	b.timer = 2;
	b.Pos = (Vector2){ 0,0 };
	b.Velocity.x = GetRandomValue(-10, 10);
	b.Velocity.y = GetRandomValue(-10, 10);

	b.Velocity = Vector2Multiply(Vector2Normalize(b.Velocity), (Vector2) { 100, 100 });

	bulletsArray[bulletIndex] = b;
	printf("Spawned bullet %d/%d\n", bulletIndex, bulletCount-1);

	bulletIndex++;
	if (bulletIndex >= bulletCount)
	{
		bulletCount += (bulletIndex - bulletCount) + 1;


		bulletsArray = realloc(bulletsArray, sizeof(Bullet) * (bulletCount));
		printf("Bullet memory alloc %d at %p\n", bulletCount, &bulletsArray);
	}
}

void BulletDespawn(Bullet* b)
{
	printf("Despawned bullet %d/%d\n", bulletIndex, bulletCount - 1);
	b->Alive = false;
	b->timer = 0;
}

void InitBulletSystem()
{
	bulletCount = 2;
	bulletsArray = calloc(bulletCount, sizeof(Bullet));
	printf("Bullet memory alloc %d at %p\n", bulletCount, &bulletsArray);
}

void UpdateBullets()
{
	int c = bulletCount;
	for (int i = c - 1; i >= 0; i--)
	{
		Bullet* b = &bulletsArray[i];

		if (!b->Alive)
			continue;

		b->timer -= GetFrameTime();

		if (b->timer <= 0)
		{
			bulletIndex = i;
			BulletDespawn(b);
			continue;
		}

		Vector2 v = b->Velocity;
		v.x *= GetFrameTime();
		v.y *= GetFrameTime();
		b->Pos = Vector2Add(b->Pos, v);
	}
}

void DrawBullets()
{
	for (int i = 0; i < bulletCount; i++)
	{
		Bullet* p = &bulletsArray[i];
		if (!p->Alive)
			continue;

		DrawCircleV(p->Pos, 12, RED);
	}
}

void EndBulletSystem()
{
	free(bulletsArray);
}