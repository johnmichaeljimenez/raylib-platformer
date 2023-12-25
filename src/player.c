#include "time.h"
#include <raylib.h>
#include <raymath.h>
#include "player.h"
#include "aabb.h"

void PlayerInit(Player *p)
{
	p->ColliderBounds = CreateBounds(p->Position, (Vector2) { 64, 96 });
	p->MovementSpeed = 300;
	p->Position = Vector2Zero();
	p->Hitbox = (Rectangle){ p->Position.x - (p->ColliderBounds.size.x/2), p->Position.y - (p->ColliderBounds.size.y / 2), p->ColliderBounds.size.x, p->ColliderBounds.size.y};

	p->Velocity = Vector2Zero();

	p->IsJumping = false;
	p->IsGrounded = false;
	p->JumpTimeToPeak = 0.45;
	p->JumpTimeToDescend = 0.4;
	p->JumpHeight = 2;
}

void PlayerUpdate(Player *p)
{
	Vector2 pos = p->Position;

	//if (IsKeyDown(KEY_W))
	//	pos.y -= p->MovementSpeed * TICKRATE;
	//if (IsKeyDown(KEY_S))
	//	pos.y += p->MovementSpeed * TICKRATE;
	//if (IsKeyDown(KEY_A))
	//	pos.x -= p->MovementSpeed * TICKRATE;
	//if (IsKeyDown(KEY_D))
	//	pos.x += p->MovementSpeed * TICKRATE;

	if (IsKeyDown(KEY_A))
		p->Velocity.x = -p->MovementSpeed * TICKRATE;
	else if (IsKeyDown(KEY_D))
		p->Velocity.x = p->MovementSpeed * TICKRATE;
	else
		p->Velocity.x = 0;

	if (p->IsGrounded)
	{
		if (!p->IsJumping)
			p->Velocity.y = 0;
		else
			p->IsJumping = false;
	}

	if (p->Velocity.y > 0)
	{
		p->Velocity.y += PlayerGetFallGravity(p) * TICKRATE;
	}
	else
	{
		p->Velocity.y += PlayerGetJumpGravity(p) * TICKRATE;

		if (p->IsJumping)
		{
			if (IsKeyReleased(KEY_SPACE))
			{
				p->Velocity.y /= 2;
				p->IsJumping = false;
			}
		}
	}

	if (p->IsGrounded)
	{
		// TODO: Add jump buffer input and coyote time
		if (IsKeyPressed(KEY_SPACE))
		{
			PlayerJump(p);
		}
	}

	if (p->Velocity.y > 30)
		p->Velocity.y = 30;

	pos = Vector2Add(pos, p->Velocity);

	p->Position = pos;
	p->ColliderBounds.position = pos;

	UpdateAABBData(&p->ColliderBounds);
	MoveAABB(&p->ColliderBounds, &p->Position);

	//p->IsGrounded = CollideBody(&(p->Position), 24);
	/*p->Hitbox.x = p->Position.x - p->HalfSize.x;
	p->Hitbox.y = p->Position.y - (p->Size.y * 0.75);*/
}

void PlayerJump(Player *p)
{
	p->Velocity.y = PlayerGetJumpVelocity(p);
	p->IsJumping = true;
	p->IsGrounded = false;
}

float PlayerGetJumpVelocity(Player *p)
{
	return ((-2 * p->JumpHeight) / p->JumpTimeToPeak);
}

float PlayerGetJumpGravity(Player *p)
{
	return ((2 * p->JumpHeight) / (p->JumpTimeToPeak * p->JumpTimeToPeak));
}

float PlayerGetFallGravity(Player *p)
{
	return ((2 * p->JumpHeight) / (p->JumpTimeToDescend * p->JumpTimeToDescend));
}

void PlayerDraw(Player *p)
{
	DrawBounds(&p->ColliderBounds, RED, false);
	//DrawRectangleRec(p->Hitbox, GREEN);
	DrawCircleV(p->Position, 4, RED);
}