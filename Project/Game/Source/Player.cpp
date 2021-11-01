#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Player.h"
#include "Map.h"
#include "Scene.h"
#include "ModuleCollisions.h"

#include "Defs.h"
#include "Log.h"

Player::Player(bool enabled) : Module(enabled)
{

	name.Create("player");

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
	jumpR.PushBack({ 50, 111, 50, 37 });
	jumpR.PushBack({ 100, 111, 50, 37 });
	jumpR.PushBack({ 0, 0, 50, 37 });
	jumpR.loop = true;
	jumpR.speed = 0.45f;

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
	jumpL.PushBack({ 300, 592, 50, 37 });
	jumpL.loop = true;
	jumpL.speed = 0.45f;



}

// Destructor
Player::~Player()
{}

// Called before render is available
bool Player::Awake(pugi::xml_node& config)
{
	LOG("Loading Player");
	bool ret = true;

	playerData.height = config.attribute("height").as_int();
	playerData.width = config.attribute("width").as_int();
	playerData.x = config.attribute("x").as_int();
	playerData.y = config.attribute("y").as_int();
	playerData.xVel = config.attribute("xVel").as_int();
	playerData.gravity = config.attribute("gravity").as_int();

	playerCollider = app->collisions->AddCollider({ playerData.x, playerData.y, playerData.width, playerData.height }, Collider::Type::PLAYER, this);

	return ret;
}

// Called before the first frame
bool Player::Start()
{
	playerTex = app->tex->Load("Assets/player/adventurer.png");


	//app->LoadGameRequest();

	currentAnimation = &idleAnimR;

	return true;
}

// Called each loop iteration
bool Player::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Player::Update(float dt)
{

	playerData.y -= playerYVel;

	// If the player is above ground, apply gravity.
	if (playerData.y < app->scene->floor) {
		// Apply gravity by reducing upward velocity.
		playerYVel -= playerData.gravity;
	}
	else {
		// Player is on the ground, so stop jumping.
		playerYVel = 0;
		jumping = false;
		// Force player to be exactly at ground level.
		playerData.y = app->scene->floor;
	}

	// Handle the player jump.
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && !jumping) {
		playerYVel = 10;
		jumping = true;
		canJumpAgain = true;
		jumpR.Reset();
		jumpL.Reset();

		if (direction == 1)
		{
			currentAnimation = &jumpR;
		}

		else if (direction == 0)
		{
			currentAnimation = &jumpL;
		}

	}
	// Handle the player DOUBLE jump.
	else if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && jumping && canJumpAgain) {
		playerYVel = 8;
		jumping = true;
		canJumpAgain = false;

		jumpR.Reset();
		jumpL.Reset();

		if (direction == 1)
		{
			currentAnimation = &jumpR;
		}

		else if (direction == 0)
		{
			currentAnimation = &jumpL;
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)

	{
		playerData.x += playerData.xVel;
		currentAnimation = &walkR;
		direction = 1;


	}
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
	{
		currentAnimation = &idleAnimR;
	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		playerData.x -= playerData.xVel;
		currentAnimation = &walkL;
		direction = 0;
	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
	{
		currentAnimation = &idleAnimL;
	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_IDLE
		&& !jumping)
	{
		if (currentAnimation != &idleAnimR
			&& currentAnimation != &idleAnimL
			&& currentAnimation != &walkR
			&& currentAnimation != &walkL
			&& currentAnimation != &jumpR
			&& currentAnimation != &jumpL)
		{
			switch (direction) {

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

	if (playerData.x > 100)
	{
		//Player POSITION LIMITS
		if (playerData.x <= app->render->playerLimitL)
		{
			playerData.x = app->render->playerLimitL;

		}

		//Camera LIMITS & MOVEMENT
		if (playerData.x >= app->render->playerLimitR)
		{
			app->render->camera.x -= playerData.xVel;
			app->render->playerLimitR += playerData.xVel;
			app->render->playerLimitL += playerData.xVel;

		}

		if (playerData.x <= app->render->playerLimitL)
		{
			app->render->camera.x += playerData.xVel;
			app->render->playerLimitL -= playerData.xVel;
			app->render->playerLimitR -= playerData.xVel;
		}

		if (playerData.x >= 3000 + (app->render->camera.w / 2))
			playerData.x = 3000 + (app->render->camera.w / 2);
	}
	if (playerData.x <= 100)
	{
		if (playerData.x <= -10)
			playerData.x = -10;
	}

	if (app->render->camera.x >= 0)
		app->render->camera.x = 0;

	if (app->render->camera.x <= -2800)
		app->render->camera.x = -2800;

	// L02: DONE 3: Request Load / Save when pressing L/S
	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->LoadGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		app->SaveGameRequest();

	//app->render->DrawTexture(img, 380, 100); // Placeholder not needed any more

	// Draw map
	app->map->Draw();

	playerCollider->SetPos(playerData.x, playerData.y);

	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
		app->map->mapData.width, app->map->mapData.height,
		app->map->mapData.tileWidth, app->map->mapData.tileHeight,
		app->map->mapData.tilesets.count());

	app->win->SetTitle(title.GetString());

	currentAnimation->Update();

	return true;
}

// Called each loop iteration
bool Player::PostUpdate()
{
	bool ret = true;

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(playerTex, playerData.x, playerData.y, &rect);

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	// After JUMP Animations, go back to IDLE Anim
	if (jumpL.loopCount > 0)
	{
		idleAnimL.Reset();
		currentAnimation = &idleAnimL;
	}
	else if (jumpR.loopCount > 0)
	{
		idleAnimR.Reset();
		currentAnimation = &idleAnimR;
	}

	jumpL.loopCount = 0;
	jumpR.loopCount = 0;

	return ret;
}

// Called before quitting
bool Player::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

bool Player::LoadPlayer(pugi::xml_node playerInf)
{
	bool ret = true;
	pugi::xml_node player = playerInf.child("player");

	if (player == NULL)
	{
		LOG("Error parsing player xml file: Cannot find 'player' tag.");
		ret = false;
	}
	else
	{
		// Load player general properties
		playerData.height = player.attribute("height").as_int();
		playerData.width = player.attribute("width").as_int();
		playerData.x = player.attribute("x").as_int();
		playerData.y = player.attribute("y").as_int();
		playerData.xVel = player.attribute("xVel").as_int();
		playerData.gravity = player.attribute("gravity").as_int();
	}

	return ret;
}