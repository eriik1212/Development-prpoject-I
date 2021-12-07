#include "Collider.h"
#include "Player.h"
#include "Scene.h"
#include "Log.h"

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
		if (intersectX < 0.0f && intersectY < 0.0f && !app->scene->godMode)
		{
			app->play->playerData.isDead = true;
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

			return true;
		}
	}
	if (type == ATTACK)
	{
		if (intersectX < 0.0f && intersectY < 0.0f)
		{
			other.Move(100, 0);
			LOG("INSIDE COLLISION");

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
	}

}