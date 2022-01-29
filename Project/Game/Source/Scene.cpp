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
#include "Enemy_Bird.h"
#include "HUD.h"
#include "Font.h"
#include "Item.h"
#include "EntityManager.h"

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
		app->hud->Enable();

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

		if (app->play->restartLVL1)
		{
			app->play->playerData.playerBody.x = 196;
			app->play->playerData.playerBody.y = 308;

			app->render->camera.x = 0;
			app->render->camera.y = 0;
			app->render->playerLimitL = 100;
			app->render->playerLimitR = 300;

			app->hud->resumeButton->state = GuiControlState::DISABLED;

			minutes = 0;
			app->timer = 0;
		}


		background_grass = app->tex->Load("Assets/textures/background_grass.png");

		background_frontmountain = app->tex->Load("Assets/textures/background_frontmountain.png");
		background_middlemountain = app->tex->Load("Assets/textures/background_middlemountain.png");
		background_backmountain = app->tex->Load("Assets/textures/background_backmountain.png");

		background_frontcloud = app->tex->Load("Assets/textures/background_frontcloud.png");
		background_middlecloud = app->tex->Load("Assets/textures/background_middlecloud.png");
		background_backcloud = app->tex->Load("Assets/textures/background_backcloud.png");

		background_sky = app->tex->Load("Assets/textures/background_sky.png");

		greenFlagLVL1 = app->tex->Load("Assets/textures/greenFlag.png");
		redFlagLVL1 = app->tex->Load("Assets/textures/redFlag.png");

		app->hud->pauseEnabled = false;

	}

	item1 = (Item*)app->entityManager->CreateEntity(EntityType::ITEM, 1, { 100,100,0,0 });
	item2 = (Item*)app->entityManager->CreateEntity(EntityType::ITEM, 2, { 100,100,0,0 });
	item3 = (Item*)app->entityManager->CreateEntity(EntityType::ITEM, 3, { 100,100,0,0 });

	

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

		app->hud->pauseEnabled = false;

		minutes = 0;
		app->timer = 0;

		app->SaveGameRequest();
	}

	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN && !app->hud->pauseEnabled && !app->hud->optionsEnabled)
	{
		//Disable Player & map
		app->play->Disable();
		app->map->Disable();
		app->scene->Disable();
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
		app->scene->Disable();
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

		app->play->restartLVL1 = true;

		app->hud->pauseEnabled = false;

	}

	if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN || app->play->playerData.isDead)
	{
		app->enemies->Disable();
		app->hud->Disable();

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
		app->render->DrawTexture(background_sky, 160 * 0, 0, true, NULL, 0);
		app->render->DrawTexture(background_sky, 160 * 1, 0, true, NULL, 0);
		app->render->DrawTexture(background_sky, 160 * 2, 0, true, NULL, 0);
		app->render->DrawTexture(background_sky, 160 * 3, 0, true, NULL, 0);
		app->render->DrawTexture(background_sky, 160 * 4, 0, true, NULL, 0);
		
		// BACK CLOUD
		app->render->DrawTexture(background_backcloud, 160 * 0, 0, true, NULL, 0.1f);
		app->render->DrawTexture(background_backcloud, 160 * 1, 0, true, NULL, 0.1f);
		app->render->DrawTexture(background_backcloud, 160 * 2, 0, true, NULL, 0.1f);
		app->render->DrawTexture(background_backcloud, 160 * 3, 0, true, NULL, 0.1f);
		app->render->DrawTexture(background_backcloud, 160 * 4, 0, true, NULL, 0.1f);

		// BACK MOUNTAIN
		app->render->DrawTexture(background_backmountain, 160 * 0, 0, true, NULL, 0.15f);
		app->render->DrawTexture(background_backmountain, 160 * 1, 0, true, NULL, 0.15f);
		app->render->DrawTexture(background_backmountain, 160 * 2, 0, true, NULL, 0.15f);
		app->render->DrawTexture(background_backmountain, 160 * 3, 0, true, NULL, 0.15f);
		app->render->DrawTexture(background_backmountain, 160 * 4, 0, true, NULL, 0.15f);
		app->render->DrawTexture(background_backmountain, 160 * 5, 0, true, NULL, 0.15f);
		app->render->DrawTexture(background_backmountain, 160 * 6, 0, true, NULL, 0.15f);

		// MIDDLE CLOUD
		app->render->DrawTexture(background_middlecloud, 160 * 0, 0, true, NULL, 0.2f);
		app->render->DrawTexture(background_middlecloud, 160 * 1, 0, true, NULL, 0.2f);
		app->render->DrawTexture(background_middlecloud, 160 * 2, 0, true, NULL, 0.2f);
		app->render->DrawTexture(background_middlecloud, 160 * 3, 0, true, NULL, 0.2f);
		app->render->DrawTexture(background_middlecloud, 160 * 4, 0, true, NULL, 0.2f);
		app->render->DrawTexture(background_middlecloud, 160 * 5, 0, true, NULL, 0.2f);
		app->render->DrawTexture(background_middlecloud, 160 * 6, 0, true, NULL, 0.2f);
		app->render->DrawTexture(background_middlecloud, 160 * 7, 0, true, NULL, 0.2f);

		// MIDDLE MOUNTAIN
		app->render->DrawTexture(background_middlemountain, 160 * 0, 0, true, NULL, 0.25f);
		app->render->DrawTexture(background_middlemountain, 160 * 1, 0, true, NULL, 0.25f);
		app->render->DrawTexture(background_middlemountain, 160 * 2, 0, true, NULL, 0.25f);
		app->render->DrawTexture(background_middlemountain, 160 * 3, 0, true, NULL, 0.25f);
		app->render->DrawTexture(background_middlemountain, 160 * 4, 0, true, NULL, 0.25f);
		app->render->DrawTexture(background_middlemountain, 160 * 5, 0, true, NULL, 0.25f);
		app->render->DrawTexture(background_middlemountain, 160 * 6, 0, true, NULL, 0.25f);
		app->render->DrawTexture(background_middlemountain, 160 * 7, 0, true, NULL, 0.25f);
		app->render->DrawTexture(background_middlemountain, 160 * 8, 0, true, NULL, 0.25f);

		// FRONT CLOUDS
		app->render->DrawTexture(background_frontcloud, 160 * 0, 0, true, NULL, 0.3f);
		app->render->DrawTexture(background_frontcloud, 160 * 1, 0, true, NULL, 0.3f);
		app->render->DrawTexture(background_frontcloud, 160 * 2, 0, true, NULL, 0.3f);
		app->render->DrawTexture(background_frontcloud, 160 * 3, 0, true, NULL, 0.3f);
		app->render->DrawTexture(background_frontcloud, 160 * 4, 0, true, NULL, 0.3f);
		app->render->DrawTexture(background_frontcloud, 160 * 5, 0, true, NULL, 0.3f);
		app->render->DrawTexture(background_frontcloud, 160 * 6, 0, true, NULL, 0.3f);
		app->render->DrawTexture(background_frontcloud, 160 * 7, 0, true, NULL, 0.3f);
		app->render->DrawTexture(background_frontcloud, 160 * 8, 0, true, NULL, 0.3f);
		app->render->DrawTexture(background_frontcloud, 160 * 9, 0, true, NULL, 0.3f);

		// FRONT MOUNTAIN
		app->render->DrawTexture(background_frontmountain, 160 * 0, 0, true, NULL, 0.35f);
		app->render->DrawTexture(background_frontmountain, 160 * 1, 0, true, NULL, 0.35f);
		app->render->DrawTexture(background_frontmountain, 160 * 2, 0, true, NULL, 0.35f);
		app->render->DrawTexture(background_frontmountain, 160 * 3, 0, true, NULL, 0.35f);
		app->render->DrawTexture(background_frontmountain, 160 * 4, 0, true, NULL, 0.35f);
		app->render->DrawTexture(background_frontmountain, 160 * 5, 0, true, NULL, 0.35f);
		app->render->DrawTexture(background_frontmountain, 160 * 6, 0, true, NULL, 0.35f);
		app->render->DrawTexture(background_frontmountain, 160 * 7, 0, true, NULL, 0.35f);
		app->render->DrawTexture(background_frontmountain, 160 * 8, 0, true, NULL, 0.35f);
		app->render->DrawTexture(background_frontmountain, 160 * 9, 0, true, NULL, 0.35f);
		app->render->DrawTexture(background_frontmountain, 160 * 10, 0, true, NULL, 0.35f);

		// GRASS
		/*app->render->DrawTexture(background_grass, 160 * 0, 0, NULL, 0.4f);
		app->render->DrawTexture(background_grass, 160 * 1, 0, NULL, 0.4f);
		app->render->DrawTexture(background_grass, 160 * 2, 0, NULL, 0.4f);
		app->render->DrawTexture(background_grass, 160 * 3, 0, NULL, 0.4f);
		app->render->DrawTexture(background_grass, 160 * 4, 0, NULL, 0.4f);
		app->render->DrawTexture(background_grass, 160 * 5, 0, NULL, 0.4f);
		app->render->DrawTexture(background_grass, 160 * 6, 0, NULL, 0.4f);
		app->render->DrawTexture(background_grass, 160 * 7, 0, NULL, 0.4f);
		app->render->DrawTexture(background_grass, 160 * 8, 0, NULL, 0.4f);
		app->render->DrawTexture(background_grass, 160 * 9, 0, NULL, 0.4f);
		app->render->DrawTexture(background_grass, 160 * 10, 0, NULL, 0.4f);
		app->render->DrawTexture(background_grass, 160 * 11, 0, NULL, 0.4f);*/
	}
	

	

	if (app->play->playerData.winner == true)
	{

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		{
			//Disable Player & map
			app->play->Disable();
			app->map->Disable();
			app->scene->Disable();
			app->enemies->Disable();
			app->hud->Disable();

			app->play->restartLVL2 = true;
			app->play->playerData.winner = false;

			app->level2->Enable();

		}

	}


	app->map->ComputePath(app->play->playerData.playerBody.x, app->play->playerData.playerBody.y);

	
	
	if (app->timer > 59)
	{
		minutes += 1;
		app->timer = 0;
		

	}
	
	sprintf_s(app->textTimer, 10, "%4d", app->timer);
	sprintf_s(textMinutes, 10, "%4d", minutes);
	sprintf_s(textPoints, 10, "%4d", app->enemies->points);
	app->font->BlitText(445-60, 10, app->hud->GameFont, textMinutes);
	app->font->BlitText(517- 60, 10, app->hud->GameFont, ":");
	
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
	app->font->BlitText(80, 70, app->hud->GameFont, "0");
	
	

	
	
	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(!app->play->chekpoint) app->render->DrawTexture(redFlagLVL1, 1480, 280, true, NULL, 1);
	else app->render->DrawTexture(greenFlagLVL1, 1480, 280, true, NULL, 1);

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