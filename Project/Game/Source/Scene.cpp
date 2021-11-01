#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Player.h"

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

	if (this->Enabled()) 
	{
		// Load music
		app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");

		//Enable Player & map
		app->play->Enable();
		app->map->Enable();

	}
	wallCollider = app->collisions->AddCollider({ 400, 300, 20, 100 }, Collider::Type::WALL, this);

	//app->LoadGameRequest();

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

	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		if (debug)
			debug = false;
		else if (!debug)
			debug = true;
	}

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
	}*/

	if(app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->LoadGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		app->SaveGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
	{
		if (collidersOn)
			collidersOn = false;
		else if (!collidersOn)
			collidersOn = true;
	}
		

	//app->render->DrawTexture(img, 380, 100); // Placeholder not needed any more

	// Draw map
	app->map->Draw();

	// L03: DONE 7: Set the window title with map/tileset info
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
				   app->map->mapData.width, app->map->mapData.height,
				   app->map->mapData.tileWidth, app->map->mapData.tileHeight,
				   app->map->mapData.tilesets.count());

	app->win->SetTitle(title.GetString());

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

	return true;
}