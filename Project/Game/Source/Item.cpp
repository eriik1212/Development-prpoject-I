#include "Item.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Player.h"
#include "Point.h"
#include "HUD.h"
#include "Level2.h"
#include "Enemies.h"

Item::Item(uint32 id, SDL_Rect bounds) : Entity(EntityType::ITEM)
{
	name.Create("item");

	redSoulTex = app->tex->Load("Assets/textures/souls.png");
	blueSoulTex = app->tex->Load("Assets/textures/souls.png");


	//RED SOUL
	redSoul.PushBack({ 0, 0, bounds.w, bounds.h });
	redSoul.PushBack({ 0 + 16 * 1, 0, bounds.w, bounds.h });
	redSoul.PushBack({ 0 + 16 * 2, 0, bounds.w, bounds.h });
	redSoul.PushBack({ 0 + 16 * 3, 0, bounds.w, bounds.h });
	redSoul.PushBack({ 0 + 16 * 4, 0, bounds.w, bounds.h });
	redSoul.PushBack({ 0 + 16 * 5, 0, bounds.w, bounds.h });
	redSoul.loop = true;
	redSoul.speed = 0.1f;

	//BLUE SOUL
	blueSoul.PushBack({ 0, 16, bounds.w, bounds.h });
	blueSoul.PushBack({ 0 + 16 * 1, 16, bounds.w, bounds.h });
	blueSoul.PushBack({ 0 + 16 * 2, 16, bounds.w, bounds.h });
	blueSoul.PushBack({ 0 + 16 * 3, 16, bounds.w, bounds.h });
	blueSoul.PushBack({ 0 + 16 * 4, 16, bounds.w, bounds.h });
	blueSoul.PushBack({ 0 + 16 * 5, 16, bounds.w, bounds.h });
	blueSoul.loop = true;
	blueSoul.speed = 0.1f;

	this->pos = iPoint(bounds.x, bounds.y);
	this->bounds = bounds;

	soulCollider = new ModuleCollisions();

	if (soulCollider != nullptr)
		soulCollider->AddCollider(bounds.x, bounds.y, bounds.w, bounds.h);

	redCurrentAnimation = &redSoul;
	blueCurrentAnimation = &blueSoul;
}

Item::~Item() {}


bool Item::Update(float dt)
{
	if (isPicked == true && soulCollider != nullptr)
	{
		if (app->hud->lifes < 6)
			app->hud->lifes++;

		if (app->hud->soulCounter < 6)
			app->hud->soulCounter += 1;

		app->enemies->points += 10;

		delete soulCollider;
		soulCollider = nullptr;
	}
	else
	{
		redCurrentAnimation->Update();
		//blueCurrentAnimation->Update();
		
	}
	return true;
}

bool Item::Draw(Render* render)
{
	if (soulCollider != nullptr)
			soulCollider->GetCollider().CheckCollision(app->play->playerData.GetCollider(), 0, SOUL);

	if (app->play->collidersOn && soulCollider != nullptr) soulCollider->GetCollider().DebugDraw(bounds, SOUL);

	// DRAW RED SOUL
	if (soulCollider != nullptr)
	{
		SDL_Rect soulRect = redCurrentAnimation->GetCurrentFrame();
		app->render->DrawTexture(redSoulTex, bounds.x, bounds.y, true, &soulRect);
	}
	

	return true;
}

bool Item::CleanUp()
{

	return true;
}