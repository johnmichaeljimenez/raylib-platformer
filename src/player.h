#include "aabb.h"

#ifndef _player_h
#define _player_h

typedef struct Player
{
	Vector2 Position;
	Bounds ColliderBounds;
	Bounds GroundCheckBounds;
	Rectangle Hitbox;

	Vector2 Velocity;

	bool IsGrounded;
	bool IsJumping;
	bool DetectedGround;
	float JumpHeight;
	float JumpTimeToPeak;
	float JumpTimeToDescend;

	float MovementSpeed;
} Player;

void PlayerInit(Player *p);
void PlayerUpdate(Player *p);
void PlayerJump(Player *p);
float PlayerGetJumpVelocity(Player *p);
float PlayerGetJumpGravity(Player *p);
float PlayerGetFallGravity(Player *p);
void PlayerDraw(Player *p);

#endif