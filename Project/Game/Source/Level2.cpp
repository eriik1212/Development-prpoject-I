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
#include "Log.h"
#include"HUD.h"

Level2::Level2(bool enabled) : Module(enabled)
{

	name.Create("level2");

	//RED SOUL
	redSoul.PushBack({ 0, 0, 16, 16 });
	redSoul.PushBack({ 0 + 16 * 1, 0, 16, 16 });
	redSoul.PushBack({ 0 + 16 * 2, 0, 16, 16 });
	redSoul.PushBack({ 0 + 16 * 3, 0, 16, 16 });
	redSoul.PushBack({ 0 + 16 * 4, 0, 16, 16 });
	redSoul.PushBack({ 0 + 16 * 5, 0, 16, 16 });
	redSoul.loop = true;
	redSoul.speed = 0.1f;

	//BLUE SOUL
	blueSoul.PushBack({ 0, 16, 16, 16 });
	blueSoul.PushBack({ 0 + 16 * 1, 16, 16, 16 });
	blueSoul.PushBack({ 0 + 16 * 2, 16, 16, 16 });
	blueSoul.PushBack({ 0 + 16 * 3, 16, 16, 16 });
	blueSoul.PushBack({ 0 + 16 * 4, 16, 16, 16 });
	blueSoul.PushBack({ 0 + 16 * 5, 16, 16, 16 });
	blueSoul.loop = true;
	blueSoul.speed = 0.1f;

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
		}

		app->SaveGameRequest();

		//Enable Player & map
		app->play->Enable();
		app->map->Enable();
		app->enemies->Enable();
		app->hud->Enable();

		soulBody.x = 890;
		soulBody.y = 308;
		soulBody.w = 16;
		soulBody.h = 16;

		soulCollider = new ModuleCollisions();

		if(soulCollider != nullptr)
		soulCollider->AddCollider(soulBody.x, soulBody.y, soulBody.w, soulBody.h);

		redCurrentAnimation = &redSoul;
		blueCurrentAnimation = &blueSoul;

		app->enemies->AddEnemy(ENEMY_TYPE::BIRD, 446, 100);

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

		redSoulTex = app->tex->Load("Assets/textures/souls.png");
		blueSoulTex = app->tex->Load("Assets/textures/souls.png");

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

		app->SaveGameRequest();
	}

	return true;
}

// Called each loop iteration
bool Level2::Update(float dt)
{
	redCurrentAnimation->Update();
	blueCurrentAnimation->Update();

	if (soulCollider != nullptr) 
		soulCollider->GetCollider().CheckCollision(app->play->playerData.GetCollider(), 0, SOUL);

	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		//Disable Player & map
		app->play->Disable();
		app->map->Disable();
		app->level2->Disable();
		app->enemies->Disable();
		app->hud->Disable();

		app->scene->Enable();
		
		app->play->restartLVL1 = true;

	}

	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		//Disable Player & map
		app->play->Disable();
		app->map->Disable();
		app->level2->Disable();
		app->enemies->Disable();
		app->hud->Disable();

		app->level2->Enable();

		app->play->restartLVL2 = true;


	}

	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		app->fade->FadeToBlack(this, this, 30);

		//Disable Player & map
		app->play->Disable();
		app->map->Disable();
		app->enemies->Disable();
		app->hud->Disable();

		app->play->restartLVL2 = true;

	}

	if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN || app->play->playerData.isDead)
	{
		app->enemies->Disable();
		app->hud->Disable();

		app->fade->FadeToBlack(this, app->gameOver, 30);
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

		app->render->DrawTexture(background_forest2, (app->render->camera.w / 6) * 0, -150, false, NULL, 0.15f);
		app->render->DrawTexture(background_forest2, (app->render->camera.w / 6) * 1, -150, false, NULL, 0.15f);
		app->render->DrawTexture(background_forest2, (app->render->camera.w / 6) * 2, -150, false, NULL, 0.15f);
		app->render->DrawTexture(background_forest2, (app->render->camera.w / 6) * 3, -150, false, NULL, 0.15f);
		app->render->DrawTexture(background_forest2, (app->render->camera.w / 6) * 4, -150, false, NULL, 0.15f);

		app->render->DrawTexture(background_forest3, (app->render->camera.w / 6) * 0, -150, false, NULL, 0.2f);
		app->render->DrawTexture(background_forest3, (app->render->camera.w / 6) * 1, -150, false, NULL, 0.2f);
		app->render->DrawTexture(background_forest3, (app->render->camera.w / 6) * 2, -150, false, NULL, 0.2f);
		app->render->DrawTexture(background_forest3, (app->render->camera.w / 6) * 3, -150, false, NULL, 0.2f);
		app->render->DrawTexture(background_forest3, (app->render->camera.w / 6) * 4, -150, false, NULL, 0.2f);

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

	// DRAW RED SOUL
	if (soulCollider != nullptr)
	{
		SDL_Rect soulRect = redCurrentAnimation->GetCurrentFrame();
		app->render->DrawTexture(redSoulTex, soulBody.x, soulBody.y, true, &soulRect);
	}

	LOG("%d", soulBody.x);

	/*if (app->play->playerData.winner == true)
	{
		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		{
			app->fade->FadeToBlack(this, app->title, 30);

			//Disable Player & map
			app->play->Disable();
			app->map->Disable();
			app->level2->Disable();
			app->enemies->Disable();

		}
	}*/


	return true;
}

// Called each loop iteration
bool Level2::PostUpdate()
{
	bool ret = true;

	if(app->play->collidersOn && soulCollider != nullptr) soulCollider->GetCollider().DebugDraw(soulBody, SOUL);

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

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
