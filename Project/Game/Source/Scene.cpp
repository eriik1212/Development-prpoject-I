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
#include "Defs.h"
#include "Log.h"

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
	//Load Map
	app->map->Load("MapLVL1.tmx");

	if (this->Enabled() && !this->Disabled()) 
	{
		// Load music
		app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");

		//Enable Player & map
		app->play->Enable();
		app->map->Enable();

	}

	background_grass = app->tex->Load("Assets/textures/background_grass.png");

	background_frontmountain = app->tex->Load("Assets/textures/background_frontmountain.png");
	background_middlemountain = app->tex->Load("Assets/textures/background_middlemountain.png");
	background_backmountain = app->tex->Load("Assets/textures/background_backmountain.png");

	background_frontcloud = app->tex->Load("Assets/textures/background_frontcloud.png");
	background_middlecloud = app->tex->Load("Assets/textures/background_middlecloud.png");
	background_backcloud = app->tex->Load("Assets/textures/background_backcloud.png");

	background_sky = app->tex->Load("Assets/textures/background_sky.png");

	app->play->playerData.isDead = false;
	debug = false;
	collidersOn = false;

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{

	return true;
}
int lastPosition;
// Called each loop iteration
bool Scene::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && debug)
	{
		app->render->camera.x -= app->play->playerData.xVel;
	}
	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && debug)
	{
		app->render->camera.x += app->play->playerData.xVel;
	}
	/*if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && debug)
	{
		app->render->camera.y -= app->play->playerData.xVel;
	}
	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && debug)
	{
		app->render->camera.y += app->play->playerData.xVel;
	}*/

	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		app->fade->FadeToBlack(this, this, 30);

		//Disable Player & map
		app->play->Disable();
		app->map->Disable();

		app->play->restart = true;

	}

	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		app->fade->FadeToBlack(this, this, 30);

		//Disable Player & map
		app->play->Disable();
		app->map->Disable();

		app->play->restart = true;
	}

	if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN || app->play->playerData.isDead)
	{
		app->fade->FadeToBlack(this, app->gameOver, 30);
	}

	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		app->SaveGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->LoadGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
	{
		if (debug)
			debug = false;
		else if (!debug)
			debug = true;
	}

	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
	{
		
		if (collidersOn)
			collidersOn = false;
		else if (!collidersOn)
			collidersOn = true;
	}

	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{

		if (godMode)
			godMode = false;
		else if (!godMode)
			godMode = true;
	}

	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
				   app->map->mapData.width, app->map->mapData.height,
				   app->map->mapData.tileWidth, app->map->mapData.tileHeight,
				   app->map->mapData.tilesets.count());

	app->win->SetTitle(title.GetString());

	// SKY
	app->render->DrawTexture(background_sky, (app->render->camera.w / 4) * 0, 0, NULL, 0);
	app->render->DrawTexture(background_sky, (app->render->camera.w / 4) * 1, 0, NULL, 0);
	app->render->DrawTexture(background_sky, (app->render->camera.w / 4) * 2, 0, NULL, 0);
	app->render->DrawTexture(background_sky, (app->render->camera.w / 4) * 3, 0, NULL, 0);

	// BACK CLOUD

	app->render->DrawTexture(background_backcloud, (app->render->camera.w / 4) * 0, 0, NULL, 0.5f, true);
	app->render->DrawTexture(background_backcloud, (app->render->camera.w / 4) * 1, 0, NULL, 0.5f, true);
	app->render->DrawTexture(background_backcloud, (app->render->camera.w / 4) * 2, 0, NULL, 0.5f, true);
	app->render->DrawTexture(background_backcloud, (app->render->camera.w / 4) * 3, 0, NULL, 0.5f, true);

	// Draw map
	app->map->Draw();

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