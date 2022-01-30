#include "Level2.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Player.h"
#include "GameOverScreen.h"
#include "FadeToBlack.h"
#include "TitleScreen.h"
#include "Enemies.h"
#include "Defs.h"
#include "Enemy_Bird.h"
#include "Enemy_Fox.h"
#include "Log.h"
#include "HUD.h"
#include "Font.h"
#include "EntityManager.h"


Level2::Level2(bool enabled) : Module(enabled)
{

	name.Create("level2");



}

// Destructor
Level2::~Level2()
{}

// Called before render is available
bool Level2::Awake(pugi::xml_node& config)
{
	LOG("Loading Level2");

	bool ret = true;

	return ret;
}

// Called before the first frame
bool Level2::Start()
{

	if (this->Enabled() && !this->Disabled())
	{
		//Load Map
		app->map->Load("MapLVL2.tmx");

		// Load music
		app->audio->StopMusic();
		app->audio->PlayMusic("Assets/audio/music/gameplay_music.ogg");

		if (app->play->restartLVL2)
		{
			app->play->playerData.playerBody.x = 80;
			app->play->playerData.playerBody.y = 348;

			app->render->camera.x = 0;
			app->render->camera.y = 0;
			app->render->playerLimitL = 100;
			app->render->playerLimitR = 300;

			//Restart timer
			app->scene->minutes = 0;
			app->timer = 0;

			app->enemies->points = 0;
			app->hud->soulCounter = 0;
		}

		app->SaveGameRequest();

		//Enable Player & map
		app->play->Enable();
		app->map->Enable();
		app->enemies->Enable();
		app->hud->Enable();

		//app->enemies->AddEnemy(ENEMY_TYPE::FOX, 1400, 100);

		app->play->playerData.isDead = false;
		app->play->debug = false;
		app->play->collidersOn = false;

		//background_sky1 = app->tex->Load("Assets/textures/dark_forest/Layer_0011_0.png");
		background_sky2 = app->tex->Load("Assets/textures/dark_forest/Layer_0010_1.png");
		background_sky3 = app->tex->Load("Assets/textures/dark_forest/Layer_0009_2.png");

		background_forest1 = app->tex->Load("Assets/textures/dark_forest/Layer_0008_3.png");
		background_forest2 = app->tex->Load("Assets/textures/dark_forest/Layer_0006_4.png");
		background_forest3 = app->tex->Load("Assets/textures/dark_forest/Layer_0005_5.png");
		background_forest4 = app->tex->Load("Assets/textures/dark_forest/Layer_0003_6.png");
		background_forest5 = app->tex->Load("Assets/textures/dark_forest/Layer_0002_7.png");

		background_lights1 = app->tex->Load("Assets/textures/dark_forest/Layer_0007_Lights.png");
		background_lights2 = app->tex->Load("Assets/textures/dark_forest/Layer_0004_Lights.png");

		background_grass1 = app->tex->Load("Assets/textures/dark_forest/Layer_0001_8.png");
		background_grass2 = app->tex->Load("Assets/textures/dark_forest/Layer_0000_9.png");


		item[0] = (Item*)app->entityManager->CreateEntity(EntityType::ITEM, 1, { 890,308,16,16 });
		item[1] = (Item*)app->entityManager->CreateEntity(EntityType::ITEM, 2, { 1698,124,16,16 });
		item[2] = (Item*)app->entityManager->CreateEntity(EntityType::ITEM, 3, { 2822,220,16,16 });
		item[3] = (Item*)app->entityManager->CreateEntity(EntityType::ITEM, 4, { 3472,212,16,16 });
		item[4] = (Item*)app->entityManager->CreateEntity(EntityType::ITEM, 5, { 5392,220,16,16 });

		app->enemies->AddEnemy(ENEMY_TYPE::BIRD, 446, 100);
		app->enemies->AddEnemy(ENEMY_TYPE::FOX, 826, 308);

		greenFlagLVL2 = app->tex->Load("Assets/textures/greenFlag.png");
		redFlagLVL2 = app->tex->Load("Assets/textures/redFlag.png");

		app->hud->pauseEnabled = false;
	}

	return true;
}

// Called each loop iteration
bool Level2::PreUpdate()
{
	if (app->play->restartLVL2)
	{
		app->play->playerData.playerBody.x = 80;
		app->play->playerData.playerBody.y = 348;

		app->render->camera.x = 0;
		app->render->camera.y = 0;
		app->render->playerLimitL = 100;
		app->render->playerLimitR = 300;

		app->play->lastLevel = 2;

		app->play->restartLVL2 = false;

		app->hud->pauseEnabled = false;

		//Restart timer
		app->scene->minutes = 0;
		app->timer = 0;

		app->SaveGameRequest();
	}

	return true;
}

// Called each loop iteration
bool Level2::Update(float dt)
{




	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN && !app->hud->pauseEnabled && !app->hud->optionsEnabled)
	{
		//Disable Player & map
		app->play->Disable();
		app->map->Disable();
		app->level2->Disable();
		app->enemies->Disable();
		app->hud->Disable();

		app->scene->Enable();

		app->play->restartLVL1 = true;

		app->hud->pauseEnabled = false;

	}

	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN && !app->hud->pauseEnabled && !app->hud->optionsEnabled)
	{
		//Disable Player & map
		app->play->Disable();
		app->map->Disable();
		app->level2->Disable();
		app->enemies->Disable();
		app->hud->Disable();

		app->level2->Enable();

		app->play->restartLVL2 = true;

		app->hud->pauseEnabled = false;

	}

	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN && !app->hud->pauseEnabled && !app->hud->optionsEnabled)
	{
		app->fade->FadeToBlack(this, this, 30);

		//Disable Player & map
		app->play->Disable();
		app->map->Disable();
		app->enemies->Disable();
		app->hud->Disable();

		app->play->restartLVL2 = true;

		app->hud->pauseEnabled = false;

	}

	if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN || app->play->playerData.isDead)
	{
		app->enemies->Disable();
		app->hud->Disable();

		app->fade->FadeToBlack(this, app->gameOver, 30);

		app->hud->pauseEnabled = false;

	}

	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		app->SaveGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->LoadGameRequest();

	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
		app->map->mapData.width, app->map->mapData.height,
		app->map->mapData.tileWidth, app->map->mapData.tileHeight,
		app->map->mapData.tilesets.count());

	//app->win->SetTitle(title.GetString());

	// ----------------------------------------------------------------------------------------------------- PARALLAX EFFECT
	{
		// SKY
		/*app->render->DrawTexture(background_sky1, (app->render->camera.w / 2) * 0, -150, false, NULL, 0);
		app->render->DrawTexture(background_sky1, (app->render->camera.w / 2) * 1, -150, false, NULL, 0);*/

		app->render->DrawTexture(background_sky2, (app->render->camera.w / 2) * 0, -150, false, NULL, 0);
		app->render->DrawTexture(background_sky2, (app->render->camera.w / 2) * 1, -150, false, NULL, 0);

		app->render->DrawTexture(background_sky3, (app->render->camera.w / 2) * 0, -150, false, NULL, 0);
		app->render->DrawTexture(background_sky3, (app->render->camera.w / 2) * 1, -150, false, NULL, 0);

		app->render->DrawTexture(background_forest1, (app->render->camera.w / 2) * 0, -150, false, NULL, 0.1f);
		app->render->DrawTexture(background_forest1, (app->render->camera.w / 2) * 1, -150, false, NULL, 0.1f);
		app->render->DrawTexture(background_forest1, (app->render->camera.w / 2) * 2, -150, false, NULL, 0.1f);
		app->render->DrawTexture(background_forest1, (app->render->camera.w / 2) * 3, -150, false, NULL, 0.1f);
		app->render->DrawTexture(background_forest1, (app->render->camera.w / 2) * 4, -150, false, NULL, 0.1f);

		app->render->DrawTexture(background_lights1, app->render->camera.w * 0, -150, false, NULL, 0.1f);
		app->render->DrawTexture(background_lights1, app->render->camera.w * 1, -150, false, NULL, 0.1f);
		app->render->DrawTexture(background_lights1, app->render->camera.w * 2, -150, false, NULL, 0.1f);
		app->render->DrawTexture(background_lights1, app->render->camera.w * 3, -150, false, NULL, 0.1f);

		app->render->DrawTexture(background_forest2, 160 * 0, -150, false, NULL, 0.15f);
		app->render->DrawTexture(background_forest2, 160 * 1, -150, false, NULL, 0.15f);
		app->render->DrawTexture(background_forest2, 160 * 2, -150, false, NULL, 0.15f);
		app->render->DrawTexture(background_forest2, 160 * 3, -150, false, NULL, 0.15f);
		app->render->DrawTexture(background_forest2, 160 * 4, -150, false, NULL, 0.15f);

		app->render->DrawTexture(background_forest3, 160 * 0, -150, false, NULL, 0.2f);
		app->render->DrawTexture(background_forest3, 160 * 1, -150, false, NULL, 0.2f);
		app->render->DrawTexture(background_forest3, 160 * 2, -150, false, NULL, 0.2f);
		app->render->DrawTexture(background_forest3, 160 * 3, -150, false, NULL, 0.2f);
		app->render->DrawTexture(background_forest3, 160 * 4, -150, false, NULL, 0.2f);

		app->render->DrawTexture(background_forest4, (app->render->camera.w / 2) * 0, -150, false, NULL, 0.25f);
		app->render->DrawTexture(background_forest4, (app->render->camera.w / 2) * 1, -150, false, NULL, 0.25f);
		app->render->DrawTexture(background_forest4, (app->render->camera.w / 2) * 2, -150, false, NULL, 0.25f);
		app->render->DrawTexture(background_forest4, (app->render->camera.w / 2) * 3, -150, false, NULL, 0.25f);
		app->render->DrawTexture(background_forest4, (app->render->camera.w / 2) * 4, -150, false, NULL, 0.25f);
		app->render->DrawTexture(background_forest4, (app->render->camera.w / 2) * 5, -150, false, NULL, 0.25f);

		app->render->DrawTexture(background_lights2, (app->render->camera.w) * 0, -150, false, NULL, 0.25f);
		app->render->DrawTexture(background_lights2, (app->render->camera.w) * 1, -150, false, NULL, 0.25f);
		app->render->DrawTexture(background_lights2, (app->render->camera.w) * 2, -150, false, NULL, 0.25f);
		app->render->DrawTexture(background_lights2, (app->render->camera.w) * 3, -150, false, NULL, 0.25f);

		app->render->DrawTexture(background_forest5, (app->render->camera.w / 2) * 0, -150, false, NULL, 0.25f);
		app->render->DrawTexture(background_forest5, (app->render->camera.w / 2) * 1, -150, false, NULL, 0.25f);
		app->render->DrawTexture(background_forest5, (app->render->camera.w / 2) * 2, -150, false, NULL, 0.25f);
		app->render->DrawTexture(background_forest5, (app->render->camera.w / 2) * 3, -150, false, NULL, 0.25f);
		app->render->DrawTexture(background_forest5, (app->render->camera.w / 2) * 4, -150, false, NULL, 0.25f);
		app->render->DrawTexture(background_forest5, (app->render->camera.w / 2) * 5, -150, false, NULL, 0.25f);

		app->render->DrawTexture(background_grass1, (app->render->camera.w / 2) * 0, -150, false, NULL, 0.3f);
		app->render->DrawTexture(background_grass1, (app->render->camera.w / 2) * 1, -150, false, NULL, 0.3f);
		app->render->DrawTexture(background_grass1, (app->render->camera.w / 2) * 2, -150, false, NULL, 0.3f);
		app->render->DrawTexture(background_grass1, (app->render->camera.w / 2) * 3, -150, false, NULL, 0.3f);
		app->render->DrawTexture(background_grass1, (app->render->camera.w / 2) * 4, -150, false, NULL, 0.3f);
		app->render->DrawTexture(background_grass1, (app->render->camera.w / 2) * 5, -150, false, NULL, 0.3f);
		app->render->DrawTexture(background_grass1, (app->render->camera.w / 2) * 6, -150, false, NULL, 0.3f);

		app->render->DrawTexture(background_grass2, (app->render->camera.w / 2) * 0, -150, false, NULL, 0.3f);
		app->render->DrawTexture(background_grass2, (app->render->camera.w / 2) * 1, -150, false, NULL, 0.3f);
		app->render->DrawTexture(background_grass2, (app->render->camera.w / 2) * 2, -150, false, NULL, 0.3f);
		app->render->DrawTexture(background_grass2, (app->render->camera.w / 2) * 3, -150, false, NULL, 0.3f);
		app->render->DrawTexture(background_grass2, (app->render->camera.w / 2) * 4, -150, false, NULL, 0.3f);
		app->render->DrawTexture(background_grass2, (app->render->camera.w / 2) * 5, -150, false, NULL, 0.3f);
		app->render->DrawTexture(background_grass2, (app->render->camera.w / 2) * 6, -150, false, NULL, 0.3f);

	}




	if (app->timer > 59)
	{
		app->scene->minutes += 1;
		app->timer = 0;


	}

	//LOG("%d", app->item->soulBody.x);

	if (app->play->playerData.winner == true)
	{
		app->play->currentAnimation = &app->play->idleAnimR;

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		{
			app->fade->FadeToBlack(this, app->title, 30);

			//Disable Player & map
			app->play->Disable();
			app->map->Disable();
			app->level2->Disable();
			app->enemies->Disable();

		}
	}

	app->entityManager->Draw();
	return true;
}

// Called each loop iteration
bool Level2::PostUpdate()
{
	bool ret = true;

	if (!app->play->chekpoint) app->render->DrawTexture(redFlagLVL2, 1480, 90, true, NULL, 1);
	else app->render->DrawTexture(greenFlagLVL2, 1480, 90, true, NULL, 1);

	sprintf_s(app->textTimer, 10, "%4d", app->timer);
	sprintf_s(app->scene->textMinutes, 10, "%4d", app->scene->minutes);
	sprintf_s(app->scene->textPoints, 10, "%4d", app->enemies->points);
	app->font->BlitText(445 - 60, 10, app->hud->GameFont, app->scene->textMinutes);
	app->font->BlitText(517 - 60, 10, app->hud->GameFont, ":");

	if (app->timer < 10)
	{
		app->font->BlitText(530 - 60, 10, app->hud->GameFont, "0");
		app->font->BlitText(490 - 60, 10, app->hud->GameFont, app->textTimer);
	}
	else
	{
		app->font->BlitText(490 - 60, 10, app->hud->GameFont, app->textTimer);
	}
	app->font->BlitText(20, 70, app->hud->GameFont, "P");
	app->font->BlitText(35, 70, app->hud->GameFont, "T");
	app->font->BlitText(50, 70, app->hud->GameFont, "S");
	app->font->BlitText(65, 70, app->hud->GameFont, ":");
	app->font->BlitText(80, 70, app->hud->GameFont, app->scene->textPoints);

	return ret;
}

// Called before quitting
bool Level2::CleanUp()
{
	LOG("Freeing level2");

	app->tex->CleanUp();
	//app->audio->CleanUp();

	return true;
}
