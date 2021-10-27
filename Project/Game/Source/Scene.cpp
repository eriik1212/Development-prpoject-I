#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{

	name.Create("scene");

	//All animations here

	//idle anim Right
	idleAnimR.PushBack({ 0, 0, 50, 37 });
	idleAnimR.PushBack({ 50, 0, 50, 37 });
	idleAnimR.PushBack({ 100, 0, 50, 37 });
	idleAnimR.PushBack({ 150, 0, 50, 37 });
	idleAnimR.loop = true;
	idleAnimR.speed = 0.02f;

	//walk Right
	walkR.PushBack({ 0, 37, 50, 37 });
	walkR.PushBack({ 50, 37, 50, 37 });
	walkR.PushBack({ 100, 37, 50, 37 });
	walkR.PushBack({ 150, 37, 50, 37 });
	walkR.PushBack({ 200, 37, 50, 37 });
	walkR.PushBack({ 250, 37, 50, 37 });
	walkR.PushBack({ 300, 37, 50, 37 });
	walkR.loop = true;
	walkR.speed = 0.02f;
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	// L03: DONE: Load map
	//app->map->Load("hello.tmx");
	app->map->Load("MapLVL1.tmx");
	playerTex = app->tex->Load("Assets/player/adventurer.png");
	// Load music
	app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");
	currentAnimation = &idleAnimR;
	player.w = 37;
	player.h = 50;
	player.x = 50;
	player.y = 50;

	debug = false;

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
	currentAnimation->Update();

	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		if (debug)
			debug = false;
		else if (!debug)
			debug = true;
	}

	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		player.x += 1;
		currentAnimation = &walkR;
		lastPosition = 1;
	}
		

	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		player.x -= 1;
		lastPosition = 0;
	}
	
	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_IDLE)
	{
		if (currentAnimation != &idleAnimR
			&& currentAnimation != &idleAnimL
			&& currentAnimation != &walkR
			&& currentAnimation != &walkL
			&& currentAnimation != &jump)
		{
			switch (lastPosition) {

			case 1:
				idleAnimR.Reset();
				currentAnimation = &idleAnimR;
				break;

			case 0:
				idleAnimL.Reset();
				currentAnimation = &idleAnimL;
				break;
			}

		}
	}
	

    // L02: DONE 3: Request Load / Save when pressing L/S
	if(app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		app->LoadGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		app->SaveGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_O) == KEY_REPEAT && debug)
		app->render->camera.x += 1;

	if(app->input->GetKey(SDL_SCANCODE_P) == KEY_REPEAT && debug)
		app->render->camera.x -= 1;

	


	if (app->render->camera.x >= 0)
		app->render->camera.x = 0;

	if (app->render->camera.x <= -2800)
		app->render->camera.x = -2800;

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
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(playerTex, player.x, player.y, &rect);
	
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
