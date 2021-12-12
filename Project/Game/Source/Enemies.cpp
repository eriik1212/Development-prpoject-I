#include "Enemies.h"

#include "App.h"
#include "Defs.h"
#include "Log.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Window.h"

#include "Player.h"

#include "Enemy.h"
#include "Enemy_Bird.h"
#include "Enemy_Fox.h"
#include "Map.h"

#define SPAWN_MARGIN 50


ModuleEnemies::ModuleEnemies(bool enabled) : Module(enabled)
{
	name.Create("enemies");

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{

	fox = app->tex->Load("Assets/enemies/fox_sprites.png");
	bird = app->tex->Load("Assets/enemies/bird_sprites.png");
	

	enemyDamageFX = app->audio->LoadFx("Assets/audio/FX/enter.wav");
	enemyDestroyedFx = app->audio->LoadFx("Assets/audio/FX/enter.wav");

	return true;
}

// Called before render is available
bool ModuleEnemies::Awake(pugi::xml_node& config)
{
	LOG("Loading Enemies");
	bool ret = true;

	app->bird_enemy->birdBody.x = config.attribute("xBird").as_int();
	app->bird_enemy->birdBody.y = config.attribute("yBird").as_int();

	app->fox_enemy->foxBody.x = config.attribute("xFox").as_int();
	app->fox_enemy->foxBody.y = config.attribute("yFox").as_int();

	return ret;
}


bool ModuleEnemies::LoadState(pugi::xml_node& data)
{
	//Load Fox Position
	app->fox_enemy->foxBody.x = data.child("enemies").child("fox").attribute("x").as_int();
	app->fox_enemy->foxBody.y = data.child("enemies").child("fox").attribute("y").as_int();

	//Load Bird Position
	app->bird_enemy->birdBody.x = data.child("bird").attribute("x").as_int();
	app->bird_enemy->birdBody.y = data.child("bird").attribute("y").as_int();

	return false;
}

bool ModuleEnemies::SaveState(pugi::xml_node& data) const
{
	//Save
	pugi::xml_node fox = data.append_child("fox");

	fox.append_attribute("x") = app->fox_enemy->foxBody.x;
	fox.append_attribute("y") = app->fox_enemy->foxBody.y;

	pugi::xml_node bird = data.append_child("bird");

	bird.append_attribute("x") = app->bird_enemy->birdBody.x;
	bird.append_attribute("y") = app->bird_enemy->birdBody.y;

	return false;
}

bool ModuleEnemies::Update(float dt)
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			enemies[i]->Update();
			if (enemies[i] != nullptr && enemies[i]->isBird)
			{
				if (enemies[i] != nullptr && app->play->playerData.playerBody.x >= (enemies[i]->position.x - 200))
				{
					app->play->inBirdView = true;

				}
				else
				{
					app->play->inBirdView = false;
				}
			}
			if (enemies[i] != nullptr && enemies[i]->isFox)
			{
				if (enemies[i] != nullptr && app->play->playerData.playerBody.x >= (enemies[i]->position.x - 200))
				{
					app->play->inFoxView = true;

				}
				else
				{
					app->play->inFoxView = false;
				}
			}
			
		}

	}

	HandleEnemiesMovement();

	HandleEnemiesDespawn();

	return true;
}

bool ModuleEnemies::PostUpdate()
{
	//PAINT ENEMIES
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			enemies[i]->Draw();
		}
	}

	return true;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPE type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type == ENEMY_TYPE::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != ENEMY_TYPE::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].x * 3 < app->render->camera.x + (app->render->camera.w * 3) + SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * app->win->GetScale());

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = ENEMY_TYPE::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			/*if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				delete enemies[i];
				enemies[i] = nullptr;
			}*/
		}
	}
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
			case ENEMY_TYPE::BIRD:
				enemies[i] = new Enemy_Bird(true, info.x, info.y);
				enemies[i]->texture = bird;
				enemies[i]->destroyedFx = enemyDestroyedFx;
				enemies[i]->damageFX = enemyDamageFX;
				enemies[i]->isBird = true;

				for (int a = 0; a < MAX_LIFE; ++a) {
					enemies[i]->lifes[a] = 1;
				}

				break;
			case ENEMY_TYPE::FOX:
				enemies[i] = new Enemy_Fox(true, info.x, info.y);
				enemies[i]->texture = fox;
				enemies[i]->destroyedFx = enemyDestroyedFx;
				enemies[i]->damageFX = enemyDamageFX;
				enemies[i]->isFox = true;

				for (int a = 0; a < MAX_LIFE; ++a) {
					enemies[i]->lifes[a] = 1;
				}

				break;
			
			}

			break;
		}
	}
}
void ModuleEnemies::UpdateLifes(unsigned short* lifes, unsigned short damage)
{

	for (int i = (MAX_LIFE - 1); i >= 0; --i) {

		if (*(lifes + i) == 0) {
			++damage;
		}
		else if (*(lifes + i) == 1 && i >= (MAX_LIFE - damage)) {
			*(lifes + i) = 0;
		}
	}
}

void ModuleEnemies::HandleEnemiesMovement()
{
	// Enemies Movement
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->isBird)
			{

				if (!enemies[i]->moving && app->play->inBirdView)
				{
					iPoint movement = enemies[i]->FlyingPath();
					enemies[i]->movingTo = app->map->MapToWorld(movement.x, movement.y);
					enemies[i]->moving = true;

					LOG("MOVING TO X %d, MOVING TO Y %d", enemies[i]->movingTo.x, enemies[i]->movingTo.y);
				}
				else
				{
					enemies[i]->movingTo = enemies[i]->position;
				}


				if (enemies[i]->movingTo.x == -32 && enemies[i]->movingTo.y == -32)
				{
					enemies[i]->moving = false;
				}
				else
				{
					// ----------------------------------------------------------------------- X

					if (enemies[i]->position.x > (enemies[i]->movingTo.x - 4) ||
						enemies[i]->position.x < (enemies[i]->movingTo.x + 4))
					{
						if (enemies[i]->movingTo.x > enemies[i]->position.x)
						{
							// For changing enemy position
							enemies[i]->position.x += enemies[i]->vel;

							// For moving the collider
							enemies[i]->birdCollider.GetCollider().Move(enemies[i]->vel, 0);

							// For drawing the collider where it has to be
							enemies[i]->birdBody.x += enemies[i]->vel;
						}
						else if (enemies[i]->movingTo.x < enemies[i]->position.x)
						{
							// For changing enemy position
							enemies[i]->position.x -= enemies[i]->vel;

							// For moving the collider
							enemies[i]->birdCollider.GetCollider().Move(-enemies[i]->vel, 0);

							// For drawing the collider where it has to be
							enemies[i]->birdBody.x -= enemies[i]->vel;
						}
					}
					else
					{
						enemies[i]->position.x = enemies[i]->movingTo.x;
					}

					// ----------------------------------------------------------------------- y

					if (enemies[i]->position.y > (enemies[i]->movingTo.y - 4) ||
						enemies[i]->position.y < (enemies[i]->movingTo.y + 4))
					{
						if (enemies[i]->movingTo.y > enemies[i]->position.y)
						{
							// For changing enemy position
							enemies[i]->position.y += enemies[i]->vel;

							// For moving the collider
							enemies[i]->birdCollider.GetCollider().Move(0, enemies[i]->vel);

							// For drawing the collider where it has to be
							enemies[i]->birdBody.y += enemies[i]->vel;
						}
						else if (enemies[i]->movingTo.y < enemies[i]->position.y)
						{
							// For changing enemy position
							enemies[i]->position.y -= enemies[i]->vel;

							// For moving the collider
							enemies[i]->birdCollider.GetCollider().Move(0, -enemies[i]->vel);

							// For drawing the collider where it has to be
							enemies[i]->birdBody.y -= enemies[i]->vel;
						}
					}
					else
					{
						enemies[i]->position.y = enemies[i]->movingTo.y;
					}
				}
				enemies[i]->moving = false;
			}
			else if (enemies[i]->isFox)
			{

				if (!enemies[i]->moving && app->play->inFoxView)
				{
					iPoint movement = enemies[i]->FloorPath();
					enemies[i]->movingTo = app->map->MapToWorld(movement.x, movement.y);
					enemies[i]->moving = true;

					LOG("MOVING TO X %d, MOVING TO Y %d", enemies[i]->movingTo.x, enemies[i]->movingTo.y);
				}
				else
				{
					enemies[i]->movingTo = enemies[i]->position;
				}


				if (enemies[i]->movingTo.x == -32 && enemies[i]->movingTo.y == -32)
				{
					enemies[i]->moving = false;
				}
				else
				{
					// ----------------------------------------------------------------------- X

					if (enemies[i]->position.x > (enemies[i]->movingTo.x - 4) ||
						enemies[i]->position.x < (enemies[i]->movingTo.x + 4))
					{
						if (enemies[i]->movingTo.x > enemies[i]->position.x)
						{
							// For changing enemy position
							enemies[i]->position.x += enemies[i]->vel;

							// For moving the collider
							enemies[i]->foxCollider.GetCollider().Move(enemies[i]->vel, 0);

							// For drawing the collider where it has to be
							enemies[i]->foxBody.x += enemies[i]->vel;
						}
						else if (enemies[i]->movingTo.x < enemies[i]->position.x)
						{
							// For changing enemy position
							enemies[i]->position.x -= enemies[i]->vel;

							// For moving the collider
							enemies[i]->foxCollider.GetCollider().Move(-enemies[i]->vel, 0);

							// For drawing the collider where it has to be
							enemies[i]->foxBody.x -= enemies[i]->vel;
						}
					}
					else
					{
						enemies[i]->position.x = enemies[i]->movingTo.x;
					}
				}
				enemies[i]->moving = false;
			}
			
		}
	}
}