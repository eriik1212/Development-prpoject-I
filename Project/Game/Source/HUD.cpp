#include "HUD.h"

#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Audio.h"
#include "ModuleCollisions.h"
#include "Input.h"

#include "Player.h"
#include "Enemies.h"
#include "Window.h"
#include "Level2.h"
#include "Scene.h"
//#include "ModuleFonts.h"


#include <stdio.h>


ModuleHUD::ModuleHUD(bool enabled) : Module(enabled)
{
	heart1.x = 0;
	heart1.y = 0;
	heart1.w = 40;
	heart1.h = 43;

	heart2.x = 0;
	heart2.y = 0;
	heart2.w = 40;
	heart2.h = 43;

	heart3.x = 0;
	heart3.y = 0;
	heart3.w = 40;
	heart3.h = 43;

	inventory.x = 0;
	inventory.y = 0;
	inventory.w = 274;
	inventory.h = 63;

	// Life's Animation
	/*lifeP1.PushBack({ 6, 233, 31, 11 });
	lifeP1.PushBack({ 40, 233, 31, 11 });
	lifeP1.PushBack({ 74, 233, 31, 11 });
	lifeP1.PushBack({ 108, 233, 31, 11 });
	lifeP1.PushBack({ 143, 233, 31, 11 });
	lifeP1.PushBack({ 177, 233, 31, 11 });
	lifeP1.PushBack({ 211, 233, 31, 11 });
	lifeP1.PushBack({ 246, 233, 31, 11 });
	lifeP1.PushBack({ 280, 233, 31, 11 });
	lifeP1.PushBack({ 314, 233, 31, 11 });
	lifeP1.PushBack({ 360, 233, 31, 11 });
	lifeP1.loop = false;*/

	
}

ModuleHUD::~ModuleHUD()
{

}

// Load assets
bool ModuleHUD::Start()
{
	bool ret = true;

	FullHeartTex = app->tex->Load("Assets/textures/full_heart.png");
	EmptyHeartTex = app->tex->Load("Assets/Introduction/empty_heart.png");
	InventoryTex = app->tex->Load("Assets/FX/inventory.png");

	// ----------------------------------------------------------------- FONTS
	//char lookupTableNumb[] = { "0123456789 " };
	//scoreFont = app->fonts->Load("Assets/Fonts/fonts.png", lookupTableNumb, 1);
	//lifeFont = app->fonts->Load("Assets/UI & HUD/num_lifes_font.png", lookupTableNumb, 1);

	return ret;
}

bool ModuleHUD::Update(float dt)
{
	
	if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN )
	{
		lifes -= 1;
	}
	
	

	return true;
}

// Update: draw background
bool ModuleHUD::PostUpdate()
{
	// Draw UI (score) --------------------------------------
	//sprintf_s(scoreTextP1, 10, "%3d", scoreP1); //P1
	//sprintf_s(scoreTextP234, 10, "%3d", scoreP234); //P234

	// Draw UI (NumLifes) --------------------------------------
	//sprintf_s(lifeText, 10, "%3d", lifes);

	if (lifes == 3)
	{
		app->render->DrawTexture(FullHeartTex, 27, 16, false, &heart1);
		app->render->DrawTexture(FullHeartTex, 80, 16, false, &heart2); 
		app->render->DrawTexture(FullHeartTex, 132, 16, false, &heart3);
	}

	else if (lifes == 2)
	{
		app->render->DrawTexture(FullHeartTex, 27, 16, false, &heart1);
		app->render->DrawTexture(FullHeartTex, 80, 16, false, &heart2);
		app->render->DrawTexture(EmptyHeartTex, 132, 16, false, &heart3);
	}

	else if (lifes == 1)
	{
		app->render->DrawTexture(FullHeartTex, 27, 16, false, &heart1);
		app->render->DrawTexture(EmptyHeartTex, 80, 16, false, &heart2);
		app->render->DrawTexture(EmptyHeartTex, 132, 16, false, &heart3);
	}

	else if (lifes == 0)
	{
		app->render->DrawTexture(EmptyHeartTex, 27, 16, false, &heart1);
		app->render->DrawTexture(EmptyHeartTex, 80, 16, false, &heart2);
		app->render->DrawTexture(EmptyHeartTex, 132, 16, false, &heart3);
	}

	app->render->DrawTexture(InventoryTex, 677, 8, false, &inventory);
	

	return true;
}

void  ModuleHUD::Reset()
{
	lifes = 3;
	
}

bool ModuleHUD::CleanUp()
{
	bool ret;

	//app->fonts->UnLoad(scoreFont);
	//app->fonts->UnLoad(lifeFont);

	return true;
}