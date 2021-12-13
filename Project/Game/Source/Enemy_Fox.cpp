#include "Enemy_Fox.h"

#include "App.h"
#include "ModuleCollisions.h"
#include "Player.h"
#include "HUD.h"
#include "Enemies.h"
#include "Enemy.h"

Enemy_Fox::Enemy_Fox(bool enabled, int x, int y) : Enemy(x, y), Module(enabled)
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

	//Collider
	foxBody.x = x;
	foxBody.y = y;
	foxBody.w = 32;
	foxBody.h = 32;

	foxCollider.AddCollider(foxBody.x, foxBody.y, foxBody.w, foxBody.h);

	coolDownFox = 0;
}


void Enemy_Fox::Update()
{
	//Check Enemy Attack Collision
	coolDownFox++;

	if (!app->play->godMode && coolDownFox > 100 && app->play->playerData.GetCollider().CheckCollision(foxCollider.GetCollider(), 0.0f, ENEMY))
	{
		//app->play->playerData.GetCollider().CheckCollision(birdCollider.GetCollider(), 0.0f, ENEMY);
		app->hud->lifes--;
		coolDownFox = 0;

	}
	else if (app->play->playerData.GetCollider().CheckCollision(foxCollider.GetCollider(), 0.0f, ENEMY) == false)
	{
		coolDownFox = 101;
	}

	if (coolDownFox >= 101) coolDownFox = 101;

	//Check Player Attack Collision
	if (app->play->playerData.attacking == true)
	{
		if (app->play->attackCollider.GetCollider().CheckCollision(foxCollider.GetCollider(), 0.0f, ATTACK))
		{
			if (app->play->playerData.direction == 1)
			{
				// For moving the collider
				foxCollider.GetCollider().Move(50, 0);

				// For drawing the collider where it has to be
				foxBody.x += 50;

				// For changing enemy position
				position.x += 50;
			}
			else
			{
				// For moving the collider
				foxCollider.GetCollider().Move(-50, 0);

				// For drawing the collider where it has to be
				foxBody.x -= 50;

				// For changing enemy position
				position.x -= 50;
			}



		}

	}

	if (app->play->collidersOn == true)
	{
		foxCollider.GetCollider().DebugDraw(foxBody, ENEMY);
	}

	//------------------------------------------------------------LEFT direcction
	if (currentAnim == &FoxIdleL) direcction = 0;
	if (currentAnim == &FoxWalkL) direcction = 0;

	//------------------------------------------------------------RIGHT ANIM direction
	if (currentAnim == &FoxIdleR) direcction = 1;
	if (currentAnim == &FoxWalkR) direcction = 1;

	if (app->enemies->foxHitted)
	{
		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (app->enemies->enemies[i] != nullptr)
			{
				if (app->enemies->enemies[i]->lifes[0] == 0)
				{
					delete app->enemies->enemies[i];
					app->enemies->enemies[i] = nullptr;
				}
			}
		}

		app->enemies->foxHitted = false;
	}

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	currentAnim = &FoxIdleL;
	 Enemy::Update();
}

