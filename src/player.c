#include "time.h"
#include <raylib.h>
#include <raymath.h>
#include "player.h"
#include "aabb.h"

static float coyoteTime = 0;
static float jumpBufferTime = 0;
static int verticalHitType = 0; //0 = none, 1 = floor, -1 = ceiling

void PlayerInit(Player* p)
{
	p->GroundCheckBounds = CreateBounds((Vector2) { p->Position.x, p->Position.y + 50 }, (Vector2) { 60, 12 });
	p->ColliderBounds = CreateBounds(p->Position, (Vector2) { 64, 96 });
	p->MovementSpeed = 300;
	p->Position = Vector2Zero();
	p->Hitbox = (Rectangle){ p->Position.x - (p->ColliderBounds.size.x / 2), p->Position.y - (p->ColliderBounds.size.y / 2), p->ColliderBounds.size.x, p->ColliderBounds.size.y };

	p->Velocity = Vector2Zero();

	p->IsJumping = false;
	p->IsGrounded = false;
	p->DetectedGround = false;
	p->JumpTimeToPeak = 0.4;
	p->JumpTimeToDescend = 0.4;
	p->JumpHeight = 3;
}

void PlayerUpdate(Player* p)
{
	if (IsKeyDown(KEY_SPACE))
	{
		jumpBufferTime = 0.1f;
	}

	Vector2 pos = p->Position;

	p->DetectedGround = IsAABBCollidingToWorld(&p->GroundCheckBounds);

	if (coyoteTime > 0)
		coyoteTime -= TICKRATE;

	if (jumpBufferTime > 0)
		jumpBufferTime -= TICKRATE;

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
		coyoteTime = 0.1f;
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
			if (IsKeyUp(KEY_SPACE))
			{
				p->Velocity.y /= 2;
				p->IsJumping = false;
			}
		}
	}

	if ((p->DetectedGround || coyoteTime > 0) && !p->IsJumping && p->Velocity.y >= 0)
	{
		if (jumpBufferTime > 0)
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
	MoveAABB(&p->ColliderBounds, &p->Position, &verticalHitType);

	p->GroundCheckBounds.position = (Vector2){ p->Position.x, p->Position.y + 50 };
	UpdateAABBData(&p->GroundCheckBounds);

	p->IsGrounded = verticalHitType == 1; //hit floor

	if ((p->IsGrounded && p->Velocity.y > 0 && !p->IsJumping) || verticalHitType == -1) //-1 = hit ceiling
		p->Velocity.y = 0;

	/*p->Hitbox.x = p->Position.x - p->HalfSize.x;
	p->Hitbox.y = p->Position.y - (p->Size.y * 0.75);*/
}

void PlayerJump(Player* p)
{
	p->Velocity.y = PlayerGetJumpVelocity(p);
	p->IsJumping = true;
	p->IsGrounded = false;
}

float PlayerGetJumpVelocity(Player* p)
{
	return ((-2 * p->JumpHeight) / p->JumpTimeToPeak);
}

float PlayerGetJumpGravity(Player* p)
{
	return ((2 * p->JumpHeight) / (p->JumpTimeToPeak * p->JumpTimeToPeak));
}

float PlayerGetFallGravity(Player* p)
{
	return ((2 * p->JumpHeight) / (p->JumpTimeToDescend * p->JumpTimeToDescend));
}

void PlayerDraw(Player* p)
{
	DrawBounds(&p->ColliderBounds, RED, false);
	DrawBounds(&p->GroundCheckBounds, RED, false);
	//DrawRectangleRec(p->Hitbox, GREEN);
	DrawCircleV(p->Position, 4, RED);
}

void PlayerDrawHUD(Player* p)
{
	DrawText(TextFormat("Velocity: %f, %f", p->Velocity.x, p->Velocity.y), 12, 30, 15, WHITE);
	DrawText(TextFormat("Jumping: %d", p->IsJumping), 12, 45, 15, WHITE);
	DrawText(TextFormat("Grounded: %d", p->IsGrounded), 12, 60, 15, WHITE);
	DrawText(TextFormat("Detected Ground: %d", p->DetectedGround), 12, 75, 15, WHITE);
	DrawText(TextFormat("Coyote Time: %f", coyoteTime), 12, 90, 15, WHITE);
	DrawText(TextFormat("Jump Buffer Time: %f", jumpBufferTime), 12, 105, 15, WHITE);
}