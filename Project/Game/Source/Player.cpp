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
	playerData.gravity = config.attribute("gravity").as_int();
	playerData.direction = config.attribute("direction").as_int();
	playerData.jumping = config.attribute("jumping").as_bool();
	playerData.canJumpAgain = config.attribute("canJumpAgain").as_bool();
	playerData.isColliding = config.attribute("isColliding").as_bool();
	playerData.isCollidingL = config.attribute("isCollidingL").as_bool();
	playerData.isCollidingR = config.attribute("isCollidingR").as_bool();

	//playerCollider = app->collisions->AddCollider({ playerData.x, playerData.y, playerData.width, playerData.height }, Collider::Type::PLAYER, this);

	return ret;
}

// Called before the first frame
bool Player::Start()
{
	playerTex = app->tex->Load("Assets/player/adventurer1.png");


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
	
	// GOD MODE (FLY)
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && app->scene->godMode)
	{
		playerData.yVel = 0;
		playerData.playerBody.y -= 8;
	}

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && app->scene->godMode)
	{
		playerData.yVel = 0;
		playerData.playerBody.y -= -8;

	}

	if(playerData.isCollidingUp == false && !app->scene->godMode)
	{
		playerData.yVel += playerData.gravity;
	}

	else if (playerData.isCollidingUp == true && !app->scene->godMode && !playerData.jumping)
	{
		app->play->playerData.yVel = -4;
		app->play->playerData.jumping = false;
	}

	// HANDLE GRAVITY & PLAYER.Y LIMITS
	if (playerData.playerBody.y >= 350 && playerData.yVel <= playerData.gravity) {
		playerData.playerBody.y = 350;
	}
	else if (playerData.playerBody.y <= 0 && playerData.yVel >= 8) {
		playerData.playerBody.y = 0;
	}
	else
	{
		playerData.playerBody.y -= playerData.yVel;
	}

	// Handle the player jump.
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && !playerData.jumping && !app->scene->godMode) {
		app->play->playerData.isCollidingUp == false;

		playerData.yVel = 10;
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
	else if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && playerData.jumping && playerData.canJumpAgain && !app->scene->godMode) {
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

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && !playerData.isCollidingL)

	{
		playerData.playerBody.x += playerData.xVel;
		currentAnimation = &walkR;
		playerData.direction = 1;

	}
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
	{
		currentAnimation = &idleAnimR;
	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && !playerData.isCollidingR)
	{
		playerData.playerBody.x -= playerData.xVel;
		currentAnimation = &walkL;
		playerData.direction = 0;
	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
	{
		currentAnimation = &idleAnimL;
	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_IDLE
		&& !playerData.jumping)
	{
		if (currentAnimation != &idleAnimR
			&& currentAnimation != &idleAnimL
			&& currentAnimation != &walkR
			&& currentAnimation != &walkL
			&& currentAnimation != &jumpR
			&& currentAnimation != &jumpL)
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
			app->render->camera.x -= playerData.xVel;
			app->render->playerLimitR += playerData.xVel;
			app->render->playerLimitL += playerData.xVel;

		}

		if (playerData.playerBody.x <= app->render->playerLimitL)
		{
			app->render->camera.x += playerData.xVel;
			app->render->playerLimitL -= playerData.xVel;
			app->render->playerLimitR -= playerData.xVel;
		}

		if (playerData.playerBody.x >= 3000 + (app->render->camera.w / 2))
			playerData.playerBody.x = 3000 + (app->render->camera.w / 2);
	}
	if (playerData.playerBody.x <= 100)
	{
		if (playerData.playerBody.x <= -10)
			playerData.playerBody.x = -10;
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

	//playerCollider->SetPos(playerData.x, playerData.y);

	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
		app->map->mapData.width, app->map->mapData.height,
		app->map->mapData.tileWidth, app->map->mapData.tileHeight,
		app->map->mapData.tilesets.count());

	app->win->SetTitle(title.GetString());

	currentAnimation->Update();

	LOG("playerX=%d", playerData.playerBody.x);
	LOG("playerYVel=%d", playerData.yVel);

	return true;
}

// Called each loop iteration
bool Player::PostUpdate()
{
	bool ret = true;

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(playerTex, playerData.playerBody.x, playerData.playerBody.y, &rect);

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

	playerData.isCollidingR = false;
	playerData.isCollidingL = false;

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
		playerData.isColliding = player.attribute("isColliding").as_bool();
		playerData.isCollidingL = player.attribute("isCollidingL").as_bool();
		playerData.isCollidingR = player.attribute("isCollidingR").as_bool();
	}

	return ret;
}

void Player::OnCollision(Collider* c1, Collider* c2)
{
	/*int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	bool isOn = false,
		isUnder = false,
		isLeft = false,
		isRight = false;

	leftA = c1->rect.x;
	rightA = c1->rect.x + c1->rect.w;
	topA = c1->rect.y;
	bottomA = c1->rect.y + c1->rect.h;

	leftB = c2->rect.x;
	rightB = c2->rect.x + c2->rect.w;
	topB = c2->rect.y;
	bottomB = c2->rect.y + c2->rect.y;

	if (rightA < (leftB + 10))
		isLeft = true;

	if (leftA > (rightB - 10))
		isRight = true;

	if (bottomA < (topB + 15))
		isOn = true;

	if (topA >= (bottomB - 5))
		isUnder = true;

	if (bottomA >= topB && isOn) 
	{ 
		// Player is on the ground, so stop jumping.
		playerData.yVel = 0;
		playerData.jumping = false;
		// Force player to be exactly at ground level.
		playerData.y = topB - playerData.height;
	}
	
	else if (topA >= bottomB && isUnder) 
	{ 
		playerData.y = bottomB;
	}

	if (rightA >= leftB && isLeft)
	{ 
		playerData.isCollidingL = true;
	}

	if (leftA <= rightB && isRight)
	{ 
		playerData.isCollidingR = true;
	}*/
}
