#include "Enemy_Bird.h"

#include "App.h"
#include "ModuleCollisions.h"
#include "Player.h"



Enemy_Bird::Enemy_Bird(bool enabled, int x, int y) : Enemy(x, y), Module(enabled)
{
	// LEFT

	//Idle anim
	leftStandB.PushBack({ 0, 0, 16, 16 });
	leftStandB.PushBack({ 16, 0, 16, 16 });
	leftStandB.PushBack({ 0, 32, 16, 16 });
	leftStandB.PushBack({ 16, 32, 16, 16 });
	leftStandB.PushBack({ 32, 32, 16, 16 });
	leftStandB.PushBack({ 16, 32, 16, 16 });
	leftStandB.PushBack({ 0, 32, 16, 16 });
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
	//idle anim
	rightStandB.PushBack({ 112, 48, 16, 16 });
	rightStandB.PushBack({ 96, 48, 16, 16 });
	rightStandB.PushBack({ 112, 80, 16, 16 });
	rightStandB.PushBack({ 96, 80, 16, 16 });
	rightStandB.PushBack({ 80, 80, 16, 16 });
	rightStandB.PushBack({ 96, 80, 16, 16 });
	rightStandB.PushBack({ 112, 80, 16, 16 });
	rightStandB.loop = true;
	rightStandB.speed = 0.15f;

	//flying
	leftFlyB.PushBack({ 112, 64, 16, 16 });
	leftFlyB.PushBack({ 112 - 16, 64, 16, 16 });
	leftFlyB.PushBack({ 112 - 16 * 2, 64, 16, 16 });
	leftFlyB.PushBack({ 112 - 16 * 3, 64, 16, 16 });
	leftFlyB.PushBack({ 112 - 16 * 4, 64, 16, 16 });
	leftFlyB.PushBack({ 112 - 16 * 5, 64, 16, 16 });
	leftFlyB.PushBack({ 112 - 16 * 6, 64, 16, 16 });
	leftFlyB.PushBack({ 112 - 16 * 7, 64, 16, 16 });
	leftFlyB.loop = true;
	leftFlyB.speed = 0.15f;

	//PATH

	//Collider
	birdBody.x = 196;
	birdBody.y = 308;
	birdBody.w = 16;
	birdBody.h = 16;

	birdCollider.AddCollider(birdBody.x, birdBody.y, birdBody.w, birdBody.h);

	//must be one algorithm of class
}


void Enemy_Bird::Update()
{
	//------------------------------------------------------------LEFT direcction
	if (currentAnim == &leftStandB)direcction = 0;
	if (currentAnim == &leftFlyB)direcction = 0;
	
	//------------------------------------------------------------LEFT ANIM direction
	if (currentAnim == &rightStandB)direcction = 1;
	if (currentAnim == &leftFlyB)direcction = 1;

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

	}*/
	
	position = spawnPos;
	currentAnim = &leftStandB;
	Enemy::Update();
}