#include "Enemy_Bird.h"

#include "App.h"
#include "ModuleCollisions.h"



Enemy_Bird::Enemy_Bird(int x, int y) : Enemy(x, y)
{
	// RIGHT 
	rightAnimO.PushBack({ 0, 830, 88, 69 });
	rightAnimO.PushBack({ 88, 830, 88, 69 });
	rightAnimO.PushBack({ 88 * 2, 830, 88, 69 });
	rightAnimO.PushBack({ 88 * 3, 830, 88, 69 });
	rightAnimO.PushBack({ 88 * 4, 830, 88, 69 });
	rightAnimO.PushBack({ 88 * 5, 830, 88, 69 });
	rightAnimO.PushBack({ 88 * 6, 830,88, 69 });
	rightAnimO.PushBack({ 88 * 7, 830, 88, 69 });
	rightAnimO.loop = true;
	rightAnimO.speed = 0.15f;

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