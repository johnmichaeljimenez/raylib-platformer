#include <raylib.h>

#ifndef BULLETS_H
#define BULLETS_H

typedef struct Bullet
{
	Vector2 Pos;
	Vector2 Velocity;
	bool Alive;
	float timer;
	int index;
} Bullet;


void BulletSpawn();
void BulletDespawn(Bullet* b);
void InitBulletSystem();
void EndBulletSystem();
void UpdateBullets();
void DrawBullets();

#endif