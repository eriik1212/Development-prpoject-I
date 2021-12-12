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
#include "TitleScreen.h"
#include "FadeToBlack.h"
#include "Level2.h"
#include "GameOverScreen.h"
#include "Enemies.h"
#include "Enemy.h"
#include "Enemy_Bird.h"
#include "HUD.h"

#include "Defs.h"
#include "Log.h"

#define CAMERA_LIMIT_LVL1 4200
#define CAMERA_LIMIT_LVL2 8600
#define PLAYER_LIMIT_LVL1 2900
#define PLAYER_LIMIT_LVL2 5900

Player::Player(bool enabled) : Module(enabled)
{

	name.Create("player");

	//All animations here
	{
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

		//death looking right
		deathAnimR.PushBack({ 200, 1332, 50, 37 });
		deathAnimR.PushBack({ 250, 1332, 50, 37 });
		deathAnimR.PushBack({ 300, 1332, 50, 37 });
		deathAnimR.PushBack({ 0, 1369, 50, 37 });
		deathAnimR.PushBack({ 50, 1369, 50, 37 });
		deathAnimR.PushBack({ 100, 1369, 50, 37 });
		deathAnimR.PushBack({ 150, 1369, 50, 37 });
		deathAnimR.PushBack({ 200, 1369, 50, 37 });
		deathAnimR.loop = true;
		deathAnimR.speed = 0.1f;

		//death looking left
		deathAnimL.PushBack({ 100, 1702, 50, 37 });
		deathAnimL.PushBack({ 50, 1702, 50, 37 });
		deathAnimL.PushBack({ 0, 1702, 50, 37 });
		deathAnimL.PushBack({ 300, 1739, 50, 37 });
		deathAnimL.PushBack({ 250, 1739, 50, 37 });
		deathAnimL.PushBack({ 200, 1739, 50, 37 });
		deathAnimL.PushBack({ 150, 1739, 50, 37 });
		deathAnimL.PushBack({ 100, 1739, 50, 37 });
		deathAnimL.loop = true;
		deathAnimL.speed = 0.1f;


		//interacting stairs left
		upStairsL.PushBack({ 100, 999, 50, 37 });
		upStairsL.PushBack({ 50, 999, 50, 37 });
		upStairsL.PushBack({ 0, 999, 50, 37 });
		upStairsL.PushBack({ 300, 1036, 50, 37 });
		upStairsL.loop = true;
		upStairsL.speed = 0.1f;


		//interacting stairs right
		upStairsR.PushBack({ 200, 407, 50, 37 });
		upStairsR.PushBack({ 250, 407, 50, 37 });
		upStairsR.PushBack({ 300, 407, 50, 37 });
		upStairsR.PushBack({ 0, 444, 50, 37 });
		upStairsR.loop = true;
		upStairsR.speed = 0.1f;


		//hit animation 1 L
		hit1L.PushBack({ 150, 1073, 50, 37 });
		hit1L.PushBack({ 100, 1073, 50, 37 });
		hit1L.PushBack({ 50, 1073, 50, 37 });
		hit1L.PushBack({ 0, 1073, 50, 37 });
		hit1L.PushBack({ 300, 1110, 50, 37 });
		hit1L.PushBack({ 250, 1110, 50, 37 });
		hit1L.loop = true;
		hit1L.speed = 0.3f;

		//hit animation 1 R
		hit1R.PushBack({ 150, 481, 49, 37 });
		hit1R.PushBack({ 200, 481, 49, 37 });
		hit1R.PushBack({ 250, 481, 49, 37 });
		hit1R.PushBack({ 300, 481, 49, 37 });
		hit1R.PushBack({ 0, 518, 49, 37 });
		hit1R.PushBack({ 50, 518, 49, 37 });
		hit1R.loop = true;
		hit1R.speed = 0.3f;

		//Player gets damaged from L
		getsDamagedL.PushBack({ 50, 1702, 50, 37 });
		getsDamagedL.PushBack({ 100, 1702, 50, 37 });
		getsDamagedL.loop = true;
		getsDamagedL.speed = 0.1f;


		//Player gets damaged from R
		getsDamagedR.PushBack({ 250, 1332, 50, 37 });
		getsDamagedR.PushBack({ 200, 1332, 50, 37 });
		getsDamagedR.loop = true;
		getsDamagedR.speed = 0.1f;
	}

}

// Destructor
Player::~Player()
{}

// Called before render is available
bool Player::Awake(pugi::xml_node& config)
{
	LOG("Loading Player");
	bool ret = true;

	playerData.playerBody.h = config.attribute("height").as_int();
	playerData.playerBody.w = config.attribute("width").as_int();
	playerData.playerBody.x = config.attribute("x").as_int();
	playerData.playerBody.y = config.attribute("y").as_int();
	playerData.xVel = config.attribute("xVel").as_int();
	playerData.yVel = config.attribute("yVel").as_int();
	playerData.maxVel = config.attribute("maxVel").as_int();
	playerData.gravity = config.attribute("gravity").as_int();
	playerData.direction = config.attribute("direction").as_int();
	playerData.jumping = config.attribute("jumping").as_bool();
	playerData.canJumpAgain = config.attribute("canJumpAgain").as_bool();
	playerData.isDead = config.attribute("isDead").as_bool();
	playerData.winner = config.attribute("winner").as_bool();
	playerData.attacking = config.attribute("attacking").as_bool();

	return ret;
}

// Called before the first frame
bool Player::Start()
{
	playerTex = app->tex->Load("Assets/player/adventurer1.png");

	winTexture = app->tex->Load("Assets/textures/youwin.png");

	CheckPointFX = app->audio->LoadFx("Assets/audio/fx/checkpoint.wav");


	chekpoint = false;

	if (app->title->cont)
	{
		app->LoadGameRequest();

	}

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

	LOG("%d", playerData.playerBody.x);
	LOG("%d", playerData.playerBody.y);
	//CAMERA
	float speed = 1 * dt;
	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && debug)
	{
		app->render->camera.x -= app->play->playerData.xVel * dt;
	}
	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && debug)
	{
		app->render->camera.x += app->play->playerData.xVel * dt;
	}
	/*if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && debug)
	{
		app->render->camera.y -= app->play->playerData.xVel;
	}
	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && debug)
	{
		app->render->camera.y += app->play->playerData.xVel;
	}*/

	//DEBUG
	if (app->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
	{
		if (debug)
			debug = false;
		else if (!debug)
			debug = true;
	}

	if (app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
	{
		app->fade->FadeToBlack(this, app->title, 30);

		//Disable Player & map
		app->play->Disable();
		app->map->Disable();
		app->level2->Disable();
		app->scene->Disable();
		app->enemies->Disable();


	}

	//Atack Collider
	if (playerData.direction == 1)
	{
		attackColliderRect.w = playerData.playerBody.w / 2;
		attackColliderRect.h = playerData.playerBody.h;
		attackColliderRect.x = playerData.playerBody.x + playerData.playerBody.w;
		attackColliderRect.y = playerData.playerBody.y;
	}
	else if (playerData.direction == 0)
	{
		attackColliderRect.w = playerData.playerBody.w / 2;
		attackColliderRect.h = playerData.playerBody.h;
		attackColliderRect.x = playerData.playerBody.x - attackColliderRect.w;
		attackColliderRect.y = playerData.playerBody.y;
	}
	attackCollider.AddCollider(attackColliderRect.x, attackColliderRect.y, attackColliderRect.w, attackColliderRect.h);

	if (playerData.yVel <= -playerData.maxVel)
	{
		playerData.yVel = -playerData.maxVel;
	}

	// GOD MODE (FLY)
	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{

		if (godMode)
			godMode = false;
		else if (!godMode)
			godMode = true;
	}

	if (godMode)
	{
		playerData.yVel = 0;
	}
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && godMode)
	{
		playerData.playerBody.y -= 8;
	}

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && godMode)
	{
		playerData.playerBody.y -= -8;

	}

	//IN LEADER
	if (inLeader)
	{
		playerData.yVel = 0;
		if (playerData.direction == 1)
		{
			currentAnimation = &upStairsR;
		}
		else if (playerData.direction == 0)
		{
			currentAnimation = &upStairsL;
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && inLeader)
	{
		playerData.playerBody.y -= 2;

		if (playerData.direction == 1)
		{
			currentAnimation = &upStairsR;
		}
		else if (playerData.direction == 0)
		{
			currentAnimation = &upStairsL;
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && inLeader)
	{
		playerData.playerBody.y -= -2;

		if (playerData.direction == 1)
		{
			currentAnimation = &upStairsR;
		}
		else if (playerData.direction == 0)
		{
			currentAnimation = &upStairsL;
		}
	}

	//COLLIDERS ON
	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
	{

		if (collidersOn)
			collidersOn = false;
		else if (!collidersOn)
			collidersOn = true;
	}

	//Floor
	if (playerData.isCollidingUp == true && !godMode)
	{
		playerData.yVel = 0;
		playerData.jumping = false;
	}

	// HANDLE GRAVITY & PLAYER.Y LIMITS
	if (playerData.playerBody.y >= 400 ) {
		playerData.playerBody.y = 399;
	}
	else if (playerData.playerBody.y <= 0 && godMode) {
		playerData.playerBody.y = 1;
	}
	else if (!godMode && !inLeader)
	{
		app->play->playerData.isCollidingUp = false;
		playerData.yVel += playerData.gravity;
		playerData.playerBody.y -= playerData.yVel;
	}

	// Handle the player jump.
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN &&
		!playerData.jumping &&
		!godMode &&
		currentAnimation != &hit1R &&
		currentAnimation != &hit1L) 
	{
		playerData.yVel = 10;
		playerData.playerBody.y -= playerData.yVel;
		playerData.jumping = true;
		playerData.canJumpAgain = true;
		jumpR.Reset();
		jumpL.Reset();

		if (playerData.direction == 1)
		{
			currentAnimation = &jumpR;
		}

		else if (playerData.direction == 0)
		{
			currentAnimation = &jumpL;
		}

	}

	// Handle the player DOUBLE jump.
	else if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN &&
		playerData.jumping &&
		playerData.canJumpAgain &&
		!godMode &&
		currentAnimation != &hit1R &&
		currentAnimation != &hit1L)
	{
		playerData.yVel = 8;
		playerData.jumping = true;
		playerData.canJumpAgain = false;

		jumpR.Reset();
		jumpL.Reset();

		if (playerData.direction == 1)
		{
			currentAnimation = &jumpR;
		}

		else if (playerData.direction == 0)
		{
			currentAnimation = &jumpL;
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT &&
		currentAnimation != &hit1R &&
		currentAnimation != &hit1L)

	{
		playerData.playerBody.x += playerData.xVel;
		currentAnimation = &walkR;
		playerData.direction = 1;

	}
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_UP &&
		currentAnimation != &hit1R &&
		currentAnimation != &hit1L)
	{
		currentAnimation = &idleAnimR;
	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT &&
		currentAnimation != &hit1R &&
		currentAnimation != &hit1L)
	{
		playerData.playerBody.x -= playerData.xVel;
		currentAnimation = &walkL;
		playerData.direction = 0;
	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_UP &&
		currentAnimation != &hit1R &&
		currentAnimation != &hit1L)
	{
		currentAnimation = &idleAnimL;
	}

	// ------------------------------------------------------------------------------------------------------ ATTACK!
	//RIGTH
	if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN &&
		!playerData.attacking &&
		playerData.direction == 1 &&
		currentAnimation != &hit1R)
	{
		playerData.attacking = true;

		hit1R.Reset();
		currentAnimation = &hit1R;	
		
		LOG("ATTACK!");
	}
	//LEFT
	else if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN &&
		!playerData.attacking && 
		playerData.direction == 0 &&
		currentAnimation != &hit1L)
	{
		playerData.attacking = true;

		hit1L.Reset();
		currentAnimation = &hit1L;

		LOG("ATTACK!");
	}
	else if (playerData.attacking)
	{
		playerData.attacking = false;
	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_P) == KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE
		&& !playerData.jumping)
	{
		if (currentAnimation != &idleAnimR
			&& currentAnimation != &idleAnimL
			&& currentAnimation != &walkR
			&& currentAnimation != &walkL
			&& currentAnimation != &jumpR
			&& currentAnimation != &jumpL
			&& currentAnimation != &hit1L
			&& currentAnimation != &hit1R
			&& currentAnimation != &upStairsL
			&& currentAnimation != &upStairsR)
		{
			switch (playerData.direction) {

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

	if (playerData.playerBody.x > 100)
	{
		//Player POSITION LIMITS
		if (playerData.playerBody.x <= app->render->playerLimitL)
		{
			playerData.playerBody.x = app->render->playerLimitL;

		}

		//Camera LIMITS & MOVEMENT
		if (playerData.playerBody.x >= app->render->playerLimitR)
		{
			app->render->camera.x -= playerData.xVel*1.5;
			app->render->playerLimitR += playerData.xVel;
			app->render->playerLimitL += playerData.xVel;

		}

		if (playerData.playerBody.x <= app->render->playerLimitL)
		{
			app->render->camera.x += playerData.xVel*1.5;
			app->render->playerLimitL -= playerData.xVel;
			app->render->playerLimitR -= playerData.xVel;
		}

		if (playerData.playerBody.x >= PLAYER_LIMIT_LVL1 + (app->render->camera.w / 2) && lastLevel == 1)
			playerData.playerBody.x = PLAYER_LIMIT_LVL1 + (app->render->camera.w / 2);

		if (playerData.playerBody.x >= PLAYER_LIMIT_LVL2 + (app->render->camera.w / 2) && lastLevel == 2)
			playerData.playerBody.x = PLAYER_LIMIT_LVL2 + (app->render->camera.w / 2);
	}
	if (playerData.playerBody.x <= 100)
	{
		if (playerData.playerBody.x <= -10)
			playerData.playerBody.x = -10;
	}

	if (app->render->camera.x >= 0)
		app->render->camera.x = 0;

	if (app->render->camera.x <= -CAMERA_LIMIT_LVL1 && lastLevel == 1)
		app->render->camera.x = -CAMERA_LIMIT_LVL1;

	if (app->render->camera.x <= -CAMERA_LIMIT_LVL2 && lastLevel == 2)
		app->render->camera.x = -CAMERA_LIMIT_LVL2;

	// CHECKPOINT!
	if (playerData.playerBody.x >= 1480 && playerData.playerBody.x <= 1484 && !chekpoint)
	{
		chekpoint = true;
		app->audio->PlayFx(CheckPointFX);
		app->SaveGameRequest();

	}


	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
		app->map->mapData.width, app->map->mapData.height,
		app->map->mapData.tileWidth, app->map->mapData.tileHeight,
		app->map->mapData.tilesets.count());

	//app->win->SetTitle(title.GetString());

	currentAnimation->Update();

	//LOG("playerX=%d", playerData.playerBody.x);
	//LOG("playerY=%d", playerData.playerBody.y);
	//LOG("playerYVel=%d", playerData.yVel);


	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(playerTex, playerData.playerBody.x - 7, playerData.playerBody.y, true, &rect);


	// Draw map
	app->map->Draw();

	return true;
}

// Called each loop iteration
bool Player::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	// After Hits Animations, go back to Idle Anim
	// HIT 
	// RIGHT
	if (hit1R.loopCount > 0)
	{
		idleAnimR.Reset();
		currentAnimation = &idleAnimR;
	}
	else if (hit1L.loopCount > 0)
	{
		idleAnimL.Reset();
		currentAnimation = &idleAnimL;
	}
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
	hit1R.loopCount = 0;
	hit1L.loopCount = 0;

	// Draw Player Colliders
	if (app->play->collidersOn)
	{
		playerData.GetCollider().DebugDraw(app->play->playerData.playerBody, PLAYER);
		attackCollider.GetCollider().DebugDraw(attackColliderRect, ATTACK);
	}

	return ret;
}

// Called before quitting
bool Player::CleanUp()
{
	LOG("Freeing Player");

	app->tex->CleanUp();

	return true;
}

bool Player::LoadState(pugi::xml_node& data)
{
	//Load Player Pos
	playerData.playerBody.x = data.child("player").attribute("x").as_int();
	playerData.playerBody.y = data.child("player").attribute("y").as_int();

	//Load Player/Camera Limits
	app->render->playerLimitL = data.child("playerLimit").attribute("Left").as_int();
	app->render->playerLimitR = data.child("playerLimit").attribute("Right").as_int();

	return true;
}

bool Player::SaveState(pugi::xml_node& data) const
{
	//Save Player Pos
	pugi::xml_node play = data.append_child("player");

	play.append_attribute("x") =playerData.playerBody.x;
	play.append_attribute("y") = playerData.playerBody.y;

	//Save Player/Camera Limits
	pugi::xml_node playLimit = data.append_child("playerLimit");

	playLimit.append_attribute("Left") = app->render->playerLimitL;
	playLimit.append_attribute("Right") = app->render->playerLimitR;

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
		playerData.playerBody.h = player.attribute("height").as_int();
		playerData.playerBody.w = player.attribute("width").as_int();
		playerData.playerBody.x = player.attribute("x").as_int();
		playerData.playerBody.y = player.attribute("y").as_int();
		playerData.xVel = player.attribute("xVel").as_int();
		playerData.yVel = player.attribute("yVel").as_int();
		playerData.gravity = player.attribute("gravity").as_int();
		playerData.direction = player.attribute("direction").as_int();
		playerData.jumping = player.attribute("jumping").as_bool();
		playerData.canJumpAgain = player.attribute("canJumpAgain").as_bool();
		playerData.isDead = player.attribute("isDead").as_bool();
	}

	return ret;
}