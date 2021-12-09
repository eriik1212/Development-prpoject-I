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
#include "Defs.h"
#include "Log.h"
#include "Level2.h"
#include "Enemies.h"

Scene::Scene(bool enabled) : Module(enabled)
{

	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");

	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{

	if (this->Enabled() && !this->Disabled()) 
	{
		//Load Map
		app->map->Load("MapLVL1.tmx");

		// Load music
		app->audio->StopMusic();
		app->audio->PlayMusic("Assets/audio/music/gameplay_music.ogg");

		//Enable Player & map
		app->play->Enable();
		app->map->Enable();
		app->enemies->Enable();

		// Iterate existing enemies
		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (app->enemies->enemies[i] != nullptr)
			{
				// Delete the enemy when it has reached the end of the screen
				delete app->enemies->enemies[i];
				app->enemies->enemies[i] = nullptr;
			}
		}
		app->enemies->AddEnemy(ENEMY_TYPE::BIRD, 196, 308);

		if (app->play->restartLVL1)
		{
			app->play->playerData.playerBody.x = 196;
			app->play->playerData.playerBody.y = 308;

			app->render->camera.x = 0;
			app->render->camera.y = 0;
			app->render->playerLimitL = 100;
			app->render->playerLimitR = 300;
		}


		background_grass = app->tex->Load("Assets/textures/background_grass.png");

		background_frontmountain = app->tex->Load("Assets/textures/background_frontmountain.png");
		background_middlemountain = app->tex->Load("Assets/textures/background_middlemountain.png");
		background_backmountain = app->tex->Load("Assets/textures/background_backmountain.png");

		background_frontcloud = app->tex->Load("Assets/textures/background_frontcloud.png");
		background_middlecloud = app->tex->Load("Assets/textures/background_middlecloud.png");
		background_backcloud = app->tex->Load("Assets/textures/background_backcloud.png");

		background_sky = app->tex->Load("Assets/textures/background_sky.png");


	}

	

	app->play->playerData.isDead = false;
	app->play->debug = false;
	app->play->collidersOn = false;

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	if (app->play->restartLVL1)
	{
		app->play->playerData.playerBody.x = 196;
		app->play->playerData.playerBody.y = 308;

		app->render->camera.x = 0;
		app->render->camera.y = 0;
		app->render->playerLimitL = 100;
		app->render->playerLimitR = 300;

		app->play->lastLevel = 1;

		app->play->restartLVL1 = false;

		app->SaveGameRequest();
	}

	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{

	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		//Disable Player & map
		app->play->Disable();
		app->map->Disable();
		app->scene->Disable();

		app->scene->Enable();
		
		app->play->restartLVL1 = true;

	}

	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		//Disable Player & map
		app->play->Disable();
		app->map->Disable();
		app->scene->Disable();

		app->level2->Enable();

		app->play->restartLVL2 = true;

	}

	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		app->fade->FadeToBlack(this, this, 30);

		//Disable Player & map
		app->play->Disable();
		app->map->Disable();

		app->play->restartLVL1 = true;
	}

	if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN || app->play->playerData.isDead)
	{
		app->fade->FadeToBlack(this, app->gameOver, 30);
	}

	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		app->SaveGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->LoadGameRequest();



	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
				   app->map->mapData.width, app->map->mapData.height,
				   app->map->mapData.tileWidth, app->map->mapData.tileHeight,
				   app->map->mapData.tilesets.count());

	//app->win->SetTitle(title.GetString());


	// ----------------------------------------------------------------------------------------------------- PARALLAX EFFECT
	{
		// SKY
		app->render->DrawTexture(background_sky, (app->render->camera.w / 6) * 0, 0, true, NULL, 0);
		app->render->DrawTexture(background_sky, (app->render->camera.w / 6) * 1, 0, true, NULL, 0);
		app->render->DrawTexture(background_sky, (app->render->camera.w / 6) * 2, 0, true, NULL, 0);
		app->render->DrawTexture(background_sky, (app->render->camera.w / 6) * 3, 0, true, NULL, 0);
		
		// BACK CLOUD
		app->render->DrawTexture(background_backcloud, (app->render->camera.w / 6) * 0, 0, true, NULL, 0.1f);
		app->render->DrawTexture(background_backcloud, (app->render->camera.w / 6) * 1, 0, true, NULL, 0.1f);
		app->render->DrawTexture(background_backcloud, (app->render->camera.w / 6) * 2, 0, true, NULL, 0.1f);
		app->render->DrawTexture(background_backcloud, (app->render->camera.w / 6) * 3, 0, true, NULL, 0.1f);
		app->render->DrawTexture(background_backcloud, (app->render->camera.w / 6) * 4, 0, true, NULL, 0.1f);

		// BACK MOUNTAIN
		app->render->DrawTexture(background_backmountain, (app->render->camera.w / 6) * 0, 0, true, NULL, 0.15f);
		app->render->DrawTexture(background_backmountain, (app->render->camera.w / 6) * 1, 0, true, NULL, 0.15f);
		app->render->DrawTexture(background_backmountain, (app->render->camera.w / 6) * 2, 0, true, NULL, 0.15f);
		app->render->DrawTexture(background_backmountain, (app->render->camera.w / 6) * 3, 0, true, NULL, 0.15f);
		app->render->DrawTexture(background_backmountain, (app->render->camera.w / 6) * 4, 0, true, NULL, 0.15f);
		app->render->DrawTexture(background_backmountain, (app->render->camera.w / 6) * 5, 0, true, NULL, 0.15f);
		app->render->DrawTexture(background_backmountain, (app->render->camera.w / 6) * 6, 0, true, NULL, 0.15f);

		// MIDDLE CLOUD
		app->render->DrawTexture(background_middlecloud, (app->render->camera.w / 6) * 0, 0, true, NULL, 0.2f);
		app->render->DrawTexture(background_middlecloud, (app->render->camera.w / 6) * 1, 0, true, NULL, 0.2f);
		app->render->DrawTexture(background_middlecloud, (app->render->camera.w / 6) * 2, 0, true, NULL, 0.2f);
		app->render->DrawTexture(background_middlecloud, (app->render->camera.w / 6) * 3, 0, true, NULL, 0.2f);
		app->render->DrawTexture(background_middlecloud, (app->render->camera.w / 6) * 4, 0, true, NULL, 0.2f);
		app->render->DrawTexture(background_middlecloud, (app->render->camera.w / 6) * 5, 0, true, NULL, 0.2f);
		app->render->DrawTexture(background_middlecloud, (app->render->camera.w / 6) * 6, 0, true, NULL, 0.2f);
		app->render->DrawTexture(background_middlecloud, (app->render->camera.w / 6) * 7, 0, true, NULL, 0.2f);

		// MIDDLE MOUNTAIN
		app->render->DrawTexture(background_middlemountain, (app->render->camera.w / 6) * 0, 0, true, NULL, 0.25f);
		app->render->DrawTexture(background_middlemountain, (app->render->camera.w / 6) * 1, 0, true, NULL, 0.25f);
		app->render->DrawTexture(background_middlemountain, (app->render->camera.w / 6) * 2, 0, true, NULL, 0.25f);
		app->render->DrawTexture(background_middlemountain, (app->render->camera.w / 6) * 3, 0, true, NULL, 0.25f);
		app->render->DrawTexture(background_middlemountain, (app->render->camera.w / 6) * 4, 0, true, NULL, 0.25f);
		app->render->DrawTexture(background_middlemountain, (app->render->camera.w / 6) * 5, 0, true, NULL, 0.25f);
		app->render->DrawTexture(background_middlemountain, (app->render->camera.w / 6) * 6, 0, true, NULL, 0.25f);
		app->render->DrawTexture(background_middlemountain, (app->render->camera.w / 6) * 7, 0, true, NULL, 0.25f);
		app->render->DrawTexture(background_middlemountain, (app->render->camera.w / 6) * 8, 0, true, NULL, 0.25f);

		// FRONT CLOUDS
		app->render->DrawTexture(background_frontcloud, (app->render->camera.w / 6) * 0, 0, true, NULL, 0.3f);
		app->render->DrawTexture(background_frontcloud, (app->render->camera.w / 6) * 1, 0, true, NULL, 0.3f);
		app->render->DrawTexture(background_frontcloud, (app->render->camera.w / 6) * 2, 0, true, NULL, 0.3f);
		app->render->DrawTexture(background_frontcloud, (app->render->camera.w / 6) * 3, 0, true, NULL, 0.3f);
		app->render->DrawTexture(background_frontcloud, (app->render->camera.w / 6) * 4, 0, true, NULL, 0.3f);
		app->render->DrawTexture(background_frontcloud, (app->render->camera.w / 6) * 5, 0, true, NULL, 0.3f);
		app->render->DrawTexture(background_frontcloud, (app->render->camera.w / 6) * 6, 0, true, NULL, 0.3f);
		app->render->DrawTexture(background_frontcloud, (app->render->camera.w / 6) * 7, 0, true, NULL, 0.3f);
		app->render->DrawTexture(background_frontcloud, (app->render->camera.w / 6) * 8, 0, true, NULL, 0.3f);
		app->render->DrawTexture(background_frontcloud, (app->render->camera.w / 6) * 9, 0, true, NULL, 0.3f);

		// FRONT MOUNTAIN
		app->render->DrawTexture(background_frontmountain, (app->render->camera.w / 6) * 0, 0, true, NULL, 0.35f);
		app->render->DrawTexture(background_frontmountain, (app->render->camera.w / 6) * 1, 0, true, NULL, 0.35f);
		app->render->DrawTexture(background_frontmountain, (app->render->camera.w / 6) * 2, 0, true, NULL, 0.35f);
		app->render->DrawTexture(background_frontmountain, (app->render->camera.w / 6) * 3, 0, true, NULL, 0.35f);
		app->render->DrawTexture(background_frontmountain, (app->render->camera.w / 6) * 4, 0, true, NULL, 0.35f);
		app->render->DrawTexture(background_frontmountain, (app->render->camera.w / 6) * 5, 0, true, NULL, 0.35f);
		app->render->DrawTexture(background_frontmountain, (app->render->camera.w / 6) * 6, 0, true, NULL, 0.35f);
		app->render->DrawTexture(background_frontmountain, (app->render->camera.w / 6) * 7, 0, true, NULL, 0.35f);
		app->render->DrawTexture(background_frontmountain, (app->render->camera.w / 6) * 8, 0, true, NULL, 0.35f);
		app->render->DrawTexture(background_frontmountain, (app->render->camera.w / 6) * 9, 0, true, NULL, 0.35f);
		app->render->DrawTexture(background_frontmountain, (app->render->camera.w / 6) * 10, 0, true, NULL, 0.35f);

		// GRASS
		/*app->render->DrawTexture(background_grass, (app->render->camera.w / 6) * 0, 0, NULL, 0.4f);
		app->render->DrawTexture(background_grass, (app->render->camera.w / 6) * 1, 0, NULL, 0.4f);
		app->render->DrawTexture(background_grass, (app->render->camera.w / 6) * 2, 0, NULL, 0.4f);
		app->render->DrawTexture(background_grass, (app->render->camera.w / 6) * 3, 0, NULL, 0.4f);
		app->render->DrawTexture(background_grass, (app->render->camera.w / 6) * 4, 0, NULL, 0.4f);
		app->render->DrawTexture(background_grass, (app->render->camera.w / 6) * 5, 0, NULL, 0.4f);
		app->render->DrawTexture(background_grass, (app->render->camera.w / 6) * 6, 0, NULL, 0.4f);
		app->render->DrawTexture(background_grass, (app->render->camera.w / 6) * 7, 0, NULL, 0.4f);
		app->render->DrawTexture(background_grass, (app->render->camera.w / 6) * 8, 0, NULL, 0.4f);
		app->render->DrawTexture(background_grass, (app->render->camera.w / 6) * 9, 0, NULL, 0.4f);
		app->render->DrawTexture(background_grass, (app->render->camera.w / 6) * 10, 0, NULL, 0.4f);
		app->render->DrawTexture(background_grass, (app->render->camera.w / 6) * 11, 0, NULL, 0.4f);*/
	}
	

	

	if (app->play->playerData.winner == true)
	{

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		{
			//Disable Player & map
			app->play->Disable();
			app->map->Disable();
			app->scene->Disable();

			app->play->restartLVL2 = true;
			app->play->playerData.winner = false;

			app->level2->Enable();

		}

	}


	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;


	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	app->tex->CleanUp();
	//app->audio->CleanUp();

	return true;
}