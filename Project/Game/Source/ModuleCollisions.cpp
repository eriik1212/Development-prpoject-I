#include "ModuleCollisions.h"

#include "App.h"

#include "Render.h"
#include "Input.h"
#include "Player.h"
#include "SString.h"
#include "SDL/include/SDL_Scancode.h"

#include "Log.h"


ModuleCollisions::ModuleCollisions()
{
}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

void ModuleCollisions::DebugDraw(SDL_Rect body, int type)
{
	Uint8 alpha = 80;
	switch (type)
	{
	case Colliders::PLAYER:
		app->render->DrawRectangle(body, 255, 255, 255, alpha);
		break;
	case Colliders::WALL:
		app->render->DrawRectangle(body, 0, 0, 255, alpha);
		break;
	}
	
}

Collider ModuleCollisions::AddCollider(int x, int y, int w, int h)
{
	colliderBody.x = x;
	colliderBody.y = y;
	colliderBody.w = w;
	colliderBody.h = h;

	//origin = iPoint(colliderBody.x + colliderBody.w / 2, colliderBody.y + colliderBody.h / 2);

	return Collider(colliderBody);
}

/*
ModuleCollisions::ModuleCollisions(bool enabled) : Module(enabled)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY_HIT] = false;

	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_HIT] = true;

	matrix[Collider::Type::ENEMY][Collider::Type::WALL] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_HIT] = false;

	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY_HIT] = false;

	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_HIT] = false;

	matrix[Collider::Type::ENEMY_HIT][Collider::Type::WALL] = false;
	matrix[Collider::Type::ENEMY_HIT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ENEMY_HIT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY_HIT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ENEMY_HIT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY_HIT][Collider::Type::ENEMY_HIT] = false;
}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

bool ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->Intersects(c2->rect))
			{
				if (matrix[c1->type][c2->type] && c1->listener)
					c1->listener->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->listener)
					c2->listener->OnCollision(c2, c1);
			}
		}
	}

	return true;
}

bool ModuleCollisions::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) {
		if (showColl)
			showColl = false;
		else if (!showColl)
			showColl = true;

		/*if (GodMode == false) {
			matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = true;
			GodMode = true;
		}
		else if (GodMode == true) {
			matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = false;
			GodMode = false;
		}

	}


	return true;
}

bool ModuleCollisions::PostUpdate()
{
	if (showColl)
	{
		DebugDraw();

	}

	return true;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case Collider::Type::NONE: // white
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case Collider::Type::WALL: // blue
			app->render->DrawRectangle(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case Collider::Type::PLAYER: // green
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 0, alpha);
			//LOG("DRAWING PLAYER HITBOX at x=%d, y=%d, w=%d, h=%d", colliders[i]->rect.x, colliders[i]->rect.y, colliders[i]->rect.w, colliders[i]->rect.h);
			break;
			/*case Collider::Type::ENEMY: // red
				app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
				break;
			case Collider::Type::PLAYER_SHOT: // yellow
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 0, alpha);
				break;
			case Collider::Type::ENEMY_SHOT: // magenta
				app->render->DrawRectangle(colliders[i]->rect, 0, 255, 255, alpha);
				break;
			case Collider::Type::ENEMY_HIT: // magenta
				app->render->DrawRectangle(colliders[i]->rect, 0, 0, 255, alpha);
				break;
		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}

*/