#include <raylib.h>

typedef struct
{
	Vector2 Position;
	Vector2 Size;
	Vector2 HalfSize;

	Vector2 Velocity;

	bool IsGrounded;
	bool IsJumping;
	float JumpHeight;
	float JumpTimeToPeak;
	float JumpTimeToDescend;

	float MovementSpeed;
} Player;

float PlayerGetJumpVelocity(Player *p);
float PlayerGetJumpGravity(Player *p);
float PlayerGetFallGravity(Player *p);

void InitPlayer(Player *p)
{
	p->Size = (Vector2){64, 96};
	p->MovementSpeed = 200;
	p->HalfSize = (Vector2){p->Size.x / 2, p->Size.y / 2};
	p->Position = Vector2Zero();

	p->Velocity = Vector2Zero();

	p->IsJumping = false;
	p->IsGrounded = false;
	p->JumpTimeToPeak = 0.45;
	p->JumpTimeToDescend = 0.4;
	p->JumpHeight = 2;
}

void UpdatePlayer(Player *p)
{
	Vector2 pos = p->Position;

	if (IsKeyDown(KEY_A))
		p->Velocity.x = -p->MovementSpeed * GetFrameTime();
	else if (IsKeyDown(KEY_D))
		p->Velocity.x = p->MovementSpeed * GetFrameTime();
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
		p->Velocity.y += PlayerGetFallGravity(p) * GetFrameTime();
	else
		p->Velocity.y += PlayerGetJumpGravity(p) * GetFrameTime();

	if (p->IsGrounded)
	{
		//TODO: Add jump buffer input and coyote time
 		if (IsKeyPressed(KEY_SPACE))
		{
			p->Velocity.y = PlayerGetJumpVelocity(p);
			p->IsJumping = true;
			p->IsGrounded = false;
		}
	}

	if (p->Velocity.y > 30)
		p->Velocity.y = 30;

	pos = Vector2Add(pos, p->Velocity);

	p->Position = pos;
	p->IsGrounded = CollideBody(&(p->Position), 32);
}

void DrawPlayer(Player *p)
{
	// DrawRectangleV(p->Position, p->Size, RED);
	DrawCircleV(p->Position, 32, RED);
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