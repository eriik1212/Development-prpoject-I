#include "Enemy_Bird.h"

#include "App.h"
#include "ModuleCollisions.h"



Enemy_Bird::Enemy_Bird(int x, int y) : Enemy(x, y)
{
	// LEFT

	//Idle anim
	leftStandB.PushBack({ 0, 0, 16, 16 });
	leftStandB.PushBack({ 16, 0, 16, 16 });
	leftStandB.PushBack({ 16 * 2, 0, 16, 16 });
	leftStandB.PushBack({ 0, 32, 16, 16 });
	leftStandB.PushBack({ 16, 32, 16, 16 });
	leftStandB.loop = true;
	leftStandB.speed = 0.15f;

	//flying
	leftFlyB.PushBack({ 0, 16, 16, 16 });
	leftFlyB.PushBack({ 16, 16, 16, 16 });
	leftFlyB.PushBack({ 16 * 2, 16, 16, 16 });
	leftFlyB.PushBack({ 16 * 3, 16, 16, 16 });
	leftFlyB.PushBack({ 16 * 4, 16, 16, 16 });
	leftFlyB.PushBack({ 16 * 5, 16, 16, 16 });
	leftFlyB.PushBack({ 16 * 6, 16, 16, 16 });
	leftFlyB.PushBack({ 16 * 7, 16, 16, 16 });
	leftFlyB.loop = true;
	leftFlyB.speed = 0.15f;



	//RIGHT



	//PATH



	//must be one algorithm of class
}


void Enemy_Bird::Update()
{
	//------------------------------------------------------------LEFT direcction
	if (currentAnim == &jumpLO)direcction = 0;
	if (currentAnim == &leftAnimO)direcction = 0;
	if (currentAnim == &punchLO)direcction = 0;

	//------------------------------------------------------------LEFT ANIM direction
	if (currentAnim == &upAnimRO)direcction = 1;
	if (currentAnim == &kickRO)direcction = 1;

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