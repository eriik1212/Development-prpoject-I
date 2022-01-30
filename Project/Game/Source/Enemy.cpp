#include "Enemy.h"

#include "App.h"
#include "ModuleCollisions.h"
#include "Textures.h"
#include "Log.h"
#include "Audio.h"
#include "Render.h"
#include "Player.h"
#include "Map.h"
#include "Enemies.h"



Enemy::Enemy(int x, int y) : 
	position(x, y)
{
	spawnPos = position;
}

Enemy::~Enemy()
{
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();


}

void Enemy::Draw()
{
	if (currentAnim != nullptr)
		app->render->DrawTexture(texture, position.x, position.y, true, &(currentAnim->GetCurrentFrame()));
}

iPoint Enemy::FlyingPath()
{
	return app->map->FlyingPathFinding(app->map->WorldToMap(position.x, position.y), 
		app->map->WorldToMap(app->play->playerData.playerBody.x, app->play->playerData.playerBody.y));
}

iPoint Enemy::FloorPath()
{
	return app->map->FloorPathFinding(app->map->WorldToMap(position.x, position.y),
		app->map->WorldToMap(app->play->playerData.playerBody.x, app->play->playerData.playerBody.y));
}


// Called before quitting
bool Enemy::CleanUp()
{
	LOG("Freeing scene");

	app->tex->CleanUp();
	//app->audio->CleanUp();

	return true;
}