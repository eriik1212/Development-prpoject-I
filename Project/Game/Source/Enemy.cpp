#include "Enemy.h"

#include "App.h"
#include "ModuleCollisions.h"
#include "Textures.h"
#include "Log.h"
#include "Audio.h"
#include "Render.h"
#include "Player.h"
#include "Map.h"



Enemy::Enemy(int x, int y) : 
	position(x, y)
{
	spawnPos = position;
}

Enemy::~Enemy()
{
	/*if (collider != nullptr)
		collider->pendingToDelete = true;
	if (HIT != nullptr)
		HIT->pendingToDelete = true;
	if (SEE != nullptr)
		SEE->pendingToDelete = true;*/
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();
	//----------------------------------------------------left collider

	/*if (collider != nullptr && direcction == 0)
		collider->SetPos(position.x + 28, position.y + 75);

	if (HIT != nullptr && direcction == 0)
		HIT->SetPos(position.x + 10, position.y + 75);*/

	//----------------------------------------------------right collider

	/*if (collider != nullptr && direcction == 1)
		collider->SetPos(position.x + 20, position.y + 75);


	if (HIT != nullptr && direcction == 1)
		HIT->SetPos(position.x + 58, position.y + 75);*/


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