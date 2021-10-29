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

#define PLAYER_SPEED 4

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
	idleAnimR.speed = 0.1f;

	//idle anim Left
	idleAnimL.PushBack({ 300, 592, 50, 37 });
	idleAnimL.PushBack({ 250, 592, 50, 37 });
	idleAnimL.PushBack({ 200, 592, 50, 37 });
	idleAnimL.PushBack({ 150, 592, 50, 37 });
	idleAnimL.loop = true;
	idleAnimL.speed = 0.1f;

	//walk Right
	walkR.PushBack({ 50, 37, 50, 37 });
	walkR.PushBack({ 100, 37, 50, 37 });
	walkR.PushBack({ 150, 37, 50, 37 });
	walkR.PushBack({ 200, 37, 50, 37 });
	walkR.PushBack({ 250, 37, 50, 37 });
	walkR.PushBack({ 300, 37, 50, 37 });
	walkR.loop = true;
	walkR.speed = 0.1f;

	//walk left
	walkL.PushBack({ 250, 629, 50, 37 });
	walkL.PushBack({ 200, 629, 50, 37 });
	walkL.PushBack({ 150, 629, 50, 37 });
	walkL.PushBack({ 100, 629, 50, 37 });
	walkL.PushBack({ 50, 629, 50, 37 });
	walkL.PushBack({ 0, 629, 50, 37 });
	walkL.loop = true;
	walkL.speed = 0.1f;

	//jump Right
	jumpR.PushBack({ 0, 74, 50, 37 });
	jumpR.PushBack({ 50, 74, 50, 37 });
	jumpR.PushBack({ 100, 74, 50, 37 });
	jumpR.PushBack({ 150, 74, 50, 37 });
	jumpR.PushBack({ 200, 74, 50, 37 });
	jumpR.PushBack({ 250, 74, 50, 37 });
	jumpR.PushBack({ 300, 74, 50, 37 });
	jumpR.PushBack({ 0, 111, 50, 37 });
	jumpR.PushBack({ 50, 37, 50, 37 });
	jumpR.PushBack({ 100, 37, 50, 37 });
	jumpR.loop = false;
	jumpR.speed = 0.1f;

	//jump Left
	jumpL.PushBack({ 300, 666, 50, 37 });
	jumpL.PushBack({ 250, 666, 50, 37 });
	jumpL.PushBack({ 200, 666, 50, 37 });
	jumpL.PushBack({ 150, 666, 50, 37 });
	jumpL.PushBack({ 100, 666, 50, 37 });
	jumpL.PushBack({ 50, 666, 50, 37 });
	jumpL.PushBack({ 0, 666, 50, 37 });
	jumpL.PushBack({ 300, 703, 50, 37 });
	jumpL.PushBack({ 250, 703, 50, 37 });
	jumpL.PushBack({ 200, 703, 50, 37 });
	jumpL.loop = false;
	jumpL.speed = 0.1f;
	


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

	//app->LoadGameRequest();

	currentAnimation = &idleAnimR;
	player.w = 37;
	player.h = 50;
	player.x = 150;
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
		player.x += PLAYER_SPEED;
		currentAnimation = &walkR;
		lastPosition = 1;

	}
		

	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		player.x -= PLAYER_SPEED;
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
			&& currentAnimation != &jumpR)
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

	if(player.x > 100)
	{
		//Player POSITION LIMITS
		if (player.x <= app->render->playerLimitL)
		{
			player.x = app->render->playerLimitL;

		}

		//Camera LIMITS & MOVEMENT
		if (player.x >= app->render->playerLimitR)
		{
			app->render->camera.x -= PLAYER_SPEED;
			app->render->playerLimitR += PLAYER_SPEED;
			app->render->playerLimitL += PLAYER_SPEED;

		}

		if (player.x <= app->render->playerLimitL )
		{
			app->render->camera.x += PLAYER_SPEED;
			app->render->playerLimitL -= PLAYER_SPEED;
			app->render->playerLimitR -= PLAYER_SPEED;
		}

		if (player.x >= 2800)
			player.x = 2800;
	}
	if (player.x <= 100)
	{
		if (player.x <= -10)
			player.x = -10;
	}

	if (app->input->GetKey(SDL_SCANCODE_O) == KEY_REPEAT && debug)
		app->render->camera.x += 1;

	if (app->input->GetKey(SDL_SCANCODE_P) == KEY_REPEAT && debug)
		app->render->camera.x -= 1;

	if (app->render->camera.x >= 0)
		app->render->camera.x = 0;

	if (app->render->camera.x <= -2800)
		app->render->camera.x = -2800;

    // L02: DONE 3: Request Load / Save when pressing L/S
	if(app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		app->LoadGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		app->SaveGameRequest();

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
