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
#include "Defs.h"
#include "Log.h"

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

		app->LoadInitialGameRequest();

		//Enable Player & map
		app->play->Enable();
		app->map->Enable();

		app->play->playerData.isDead = false;
		app->play->debug = false;
		app->play->collidersOn = false;
	}



	return true;
}

// Called each loop iteration
bool Level2::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool Level2::Update(float dt)
{

	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		//Disable Player & map
		app->play->Disable();
		app->map->Disable();

		app->fade->FadeToBlack(this, app->scene, 30);

		app->play->restart = true;

	}

	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		//Disable Player & map
		app->play->Disable();
		app->map->Disable();

		app->fade->FadeToBlack(this, app->level2, 30);

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

	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->LoadGameRequest();

	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
		app->map->mapData.width, app->map->mapData.height,
		app->map->mapData.tileWidth, app->map->mapData.tileHeight,
		app->map->mapData.tilesets.count());

	//app->win->SetTitle(title.GetString());


	// ----------------------------------------------------------------------------------------------------- PARALLAX EFFECT


	/*if (app->play->playerData.winner == true)
	{

		app->render->DrawTexture(winTexture, app->render->camera.w / 6, app->render->camera.h / 6, true, NULL, 0);

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
			app->fade->FadeToBlack(this, app->title, 30);

		app->play->revive = true;
	}*/


	return true;
}

// Called each loop iteration
bool Level2::PostUpdate()
{
	bool ret = true;


	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Level2::CleanUp()
{
	LOG("Freeing scene");

	app->tex->CleanUp();
	//app->audio->CleanUp();

	return true;
}
