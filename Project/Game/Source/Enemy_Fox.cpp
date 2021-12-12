#include "Enemy_Fox.h"

#include "App.h"
#include "ModuleCollisions.h"



Enemy_Fox::Enemy_Fox(int x, int y) : Enemy(x, y)
{
	// Idle animation to right
	FoxIdleR.PushBack({ 0, 0, 32, 32 });
	FoxIdleR.PushBack({ 32, 0, 32, 32 });
	FoxIdleR.PushBack({ 32 * 2, 0, 32, 32 });
	FoxIdleR.PushBack({ 32 * 3, 0, 32, 32 });
	FoxIdleR.PushBack({ 32 * 4, 0, 32, 32 });
	FoxIdleR.loop = true;
	FoxIdleR.speed = 0.15f;

	// Idle animation to left
	FoxIdleL.PushBack({ 416, 224, 32, 32 });
	FoxIdleL.PushBack({ 416 - 32, 224, 32, 32 });
	FoxIdleL.PushBack({ 416 - 32 * 2, 224, 32, 32 });
	FoxIdleL.PushBack({ 416 - 32 * 3, 224, 32, 32 });
	FoxIdleL.PushBack({ 416 - 32 * 4, 224, 32, 32 });
	FoxIdleL.loop = true;
	FoxIdleL.speed = 0.15f;

	//Walk to right
	FoxWalkR.PushBack({ 416, 64, 32, 32 });
	FoxWalkR.PushBack({ 32, 64, 32, 32 });
	FoxWalkR.PushBack({ 32 * 2, 64, 32, 32 });
	FoxWalkR.PushBack({ 32 * 3, 64, 32, 32 });
	FoxWalkR.PushBack({ 32 * 4, 64, 32, 32 });
	FoxWalkR.PushBack({ 32 * 5, 64, 32, 32 });
	FoxWalkR.PushBack({ 32 * 6, 64, 32, 32 });
	FoxWalkR.PushBack({ 32 * 7, 64, 32, 32 });
	FoxWalkR.loop = true;
	FoxWalkR.speed = 0.15f;

	//Walk to left
	FoxWalkL.PushBack({ 416, 288, 32, 32 });
	FoxWalkL.PushBack({ 416 - 32, 288, 32, 32 });
	FoxWalkL.PushBack({ 416 - 32 * 2, 288, 32, 32 });
	FoxWalkL.PushBack({ 416 - 32 * 3, 288, 32, 32 });
	FoxWalkL.PushBack({ 416 - 32 * 4, 288, 32, 32 });
	FoxWalkL.PushBack({ 416 - 32 * 5, 288, 32, 32 });
	FoxWalkL.PushBack({ 416 - 32 * 6, 288, 32, 32 });
	FoxWalkL.PushBack({ 416 - 32 * 7, 288, 32, 32 });
	FoxWalkL.loop = true;
	FoxWalkL.speed = 0.15f;

	//PATH



	//must be one algorithm of class
}


void Enemy_Fox::Update()
{
	//------------------------------------------------------------LEFT direcction
	/*if (currentAnim == &jumpLO)direcction = 0;
	if (currentAnim == &leftAnimO)direcction = 0;
	if (currentAnim == &punchLO)direcction = 0;*/

	//------------------------------------------------------------LEFT ANIM direction
	/*if (currentAnim == &upAnimRO)direcction = 1;
	if (currentAnim == &kickRO)direcction = 1;*/

	/*if (app->collisions->GodMode == true) {


		app->collisions->matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_HIT] = false;


		if (coolTime >= coolDown) {

			if (currentAnim == &punchLO)
			{
				app->collisions->matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_HIT] = true;
				coolTime = 0.0f;

			}
			else if (currentAnim == &kickRO)
			{
				app->collisions->matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_HIT] = true;
				coolTime = 0.0f;
			}
			else
				app->collisions->matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_HIT] = false;
		}
		else
			coolTime += 0.1f;

	}

	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();*/

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	 Enemy::Update();
}