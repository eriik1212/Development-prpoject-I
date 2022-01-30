#include "Collider.h"
#include "Player.h"
#include "Scene.h"
#include "Level2.h"
#include "Log.h"
#include "Enemy_Bird.h"
#include "Enemies.h"
#include "Enemy.h"
#include "HUD.h"

Collider::Collider(SDL_Rect& body) :
	body(body)
{
}

Collider::~Collider()
{
	
}

bool Collider::CheckCollision(Collider& other, float push, CollidersType type)
{

	iPoint otherPosition = other.GetPosition();
	iPoint otherHalfSize = other.GetHalfSize();
	iPoint thisPosition = GetPosition();
	iPoint thisHalfSize = GetHalfSize();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (type == WALL)
	{
		if (intersectX < 0.0f && intersectY < 0.0f)
		{
			push = std::min(std::max(push, 0.0f), 1.0f);

			if (intersectX > intersectY)
			{
				if (deltaX > 0.0f)
				{
					Move(intersectX * (1.0f - push), 0.0f);
					other.Move(-intersectX * push, 0.0f);

				}
				else
				{
					Move(-intersectX * (1.0f - push), 0.0f);
					other.Move(intersectX * push, 0.0f);
				}
			}
			else
			{
				if (deltaY > 0.0f)
				{
					Move(0.0f, intersectY * (1.0f - push));
					other.Move(0.0f, -intersectY * push);

				}
				else
				{
					Move(0.0f, -intersectY * (1.0f - push));
					other.Move(0.0f, intersectY * push);

					app->play->playerData.isCollidingUp = true;

				}
			}

			return true;
		}
	}
	if (type == DEAD)
	{
		if (intersectX < 0.0f && intersectY < 0.0f && !app->play->godMode)
		{
			app->hud->lifes = 0;
			app->play->playerData.jumping = true;
			app->play->playerData.canJumpAgain = false;

			return true;
		}
	}
	if (type == WIN)
	{
		if (intersectX < 0.0f && intersectY < 0.0f)
		{
			app->play->playerData.winner = true;

			app->render->DrawTexture(app->play->winTexture, app->render->camera.w / 6, app->render->camera.h / 6, true, NULL, 0);

			return true;
		}
	}
	if (type == ATTACK)
	{
		if (intersectX < 0.0f && intersectY < 0.0f)
		{

			app->enemies->birdHitted = true;

			for (uint i = 0; i < MAX_ENEMIES; ++i)
			{
				if (app->enemies->enemies[i] != nullptr)
				{
					app->enemies->UpdateLifes(app->enemies->enemies[i],app->enemies->enemies[i]->lifes, 1);
					
				}
			}

			LOG("INSIDE COLLISION");

			return true;
		}
	}
	if (type == LEADER)
	{
		if (intersectX < -15.0f && intersectY < 200.0f)
		{
			app->play->inLeader = true;

			return true;
		}
		else
		{
			app->play->inLeader = false;

		}
	}
	if (type == ENEMY)
	{
		if (intersectX < 0.0f && intersectY < 0.0f)
		{
			//LOG("Enemy Attacks!");

			return true;
		}
	}
	if (type == SOUL)
	{
		if (intersectX < 0.0f && intersectY < 0.0f)
		{
			for (int i = 0; i < MAX_ITEMS; i++)
			{
				if (app->play->playerData.playerBody.x - app->level2->item[i]->bounds.x > -app->play->playerData.playerBody.w && app->level2->item[i]->bounds.x - app->play->playerData.playerBody.x < app->play->playerData.playerBody.w)
				{
					app->level2->item[i]->isPicked = true;
				}
			}
			
			LOG("SOUL PICKED UP!");

			return true;
		}
	}

	return false;
}

void Collider::DebugDraw(SDL_Rect body, int type)
{
	Uint8 alpha = 80;
	switch (type)
	{
	case CollidersType::PLAYER:
		app->render->DrawRectangle(body, 0, 255, 0, alpha);
		break;
	case CollidersType::WALL:
		app->render->DrawRectangle(body, 0, 0, 255, alpha);
		break;
	case CollidersType::DEAD:
		app->render->DrawRectangle(body, 255, 0, 0, alpha);
		break;
	case CollidersType::WIN:
		app->render->DrawRectangle(body, 255, 255, 0, alpha);
		break;
	case CollidersType::ATTACK:
		app->render->DrawRectangle(body, 125, 255, 125, alpha);
		break;
	case CollidersType::LEADER:
		app->render->DrawRectangle(body, 0, 255, 125, alpha);
		break;
	case CollidersType::ENEMY:
		app->render->DrawRectangle(body, 255, 0, 255, alpha);
		break;
	case CollidersType::SOUL:
		app->render->DrawRectangle(body, 0, 125, 255, alpha);
		break;
	}

}