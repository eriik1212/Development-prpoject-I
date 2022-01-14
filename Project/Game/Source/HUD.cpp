#include "HUD.h"

#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Audio.h"
#include "ModuleCollisions.h"
#include "Input.h"
#include "Font.h"

#include "Player.h"
#include "Enemies.h"
#include "Window.h"
#include "Level2.h"
#include "Scene.h"
#include "Font.h"
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

	soul1.x = 0;
	soul1.y = 0;
	soul1.w = 17;
	soul1.h = 17;

	soul2.x = 0;
	soul2.y = 0;
	soul2.w = 17;
	soul2.h = 17;

	soul3.x = 0;
	soul3.y = 0;
	soul3.w = 17;
	soul3.h = 17;

	soul4.x = 0;
	soul4.y = 0;
	soul4.w = 17;
	soul4.h = 17;

	soul5.x = 0;
	soul5.y = 0;
	soul5.w = 17;
	soul5.h = 17;

	soul6.x = 0;
	soul6.y = 0;
	soul6.w = 17;
	soul6.h = 17;


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

	char lookupTableNumb[] = { "z!{#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[/]^_ abcdefghijklmnopqrstuvwxy" };
	FullHeartTex = app->tex->Load("Assets/textures/full_heart.png");
	EmptyHeartTex = app->tex->Load("Assets/textures/empty_heart.png");
	InventoryTex = app->tex->Load("Assets/textures/inventory.png");
	DarkSoul= app->tex->Load("Assets/textures/dark_fire.png");
	GameFont = app->font->Load("Assets/Fonts/font1.png",lookupTableNumb, 6);

	Reset();

	// ----------------------------------------------------------------- FONTS
	//char lookupTableNumb[] = { "0123456789 " };
	//scoreFont = app->fonts->Load("Assets/Fonts/fonts.png", lookupTableNumb, 1);
	//lifeFont = app->fonts->Load("Assets/UI & HUD/num_lifes_font.png", lookupTableNumb, 1);

	return ret;
}

bool ModuleHUD::Update(float dt)
{

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

	if (app->scene->Enabled() || app->level2->Enabled())
	{

		if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && !pauseEnabled)
		{
			
			pauseEnabled = true;
		}
		else if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && pauseEnabled)
		{
			pauseEnabled = false;
		}

		if (pauseEnabled)
		{
			DrawPauseMenu();

		}

		if (lifes >= 6) lifes = 5;

		if (lifes == 5)
		{
			app->render->DrawTexture(FullHeartTex, 27, 16, false, &heart1, NULL);
			app->render->DrawTexture(FullHeartTex, 80, 16, false, &heart2, NULL);
			app->render->DrawTexture(FullHeartTex, 133, 16, false, &heart3, NULL);
			app->render->DrawTexture(FullHeartTex, 186, 16, false, &heart3, NULL);
			app->render->DrawTexture(FullHeartTex, 239, 16, false, &heart3, NULL);
		}

		else if (lifes == 4)
		{
			app->render->DrawTexture(FullHeartTex, 27, 16, false, &heart1, NULL);
			app->render->DrawTexture(FullHeartTex, 80, 16, false, &heart2, NULL);
			app->render->DrawTexture(FullHeartTex, 133, 16, false, &heart3, NULL);
			app->render->DrawTexture(FullHeartTex, 186, 16, false, &heart3, NULL);
			app->render->DrawTexture(EmptyHeartTex, 239, 16, false, &heart3, NULL);
		}

		else if (lifes == 3)
		{
			app->render->DrawTexture(FullHeartTex, 27, 16, false, &heart1, NULL);
			app->render->DrawTexture(FullHeartTex, 80, 16, false, &heart2, NULL);
			app->render->DrawTexture(FullHeartTex, 133, 16, false, &heart3, NULL);
			app->render->DrawTexture(EmptyHeartTex, 186, 16, false, &heart3, NULL);
			app->render->DrawTexture(EmptyHeartTex, 239, 16, false, &heart3, NULL);

		}

		else if (lifes == 2)
		{
			app->render->DrawTexture(FullHeartTex, 27, 16, false, &heart1, NULL);
			app->render->DrawTexture(FullHeartTex, 80, 16, false, &heart2, NULL);
			app->render->DrawTexture(EmptyHeartTex, 133, 16, false, &heart3, NULL);
			app->render->DrawTexture(EmptyHeartTex, 186, 16, false, &heart3, NULL);
			app->render->DrawTexture(EmptyHeartTex, 239, 16, false, &heart3, NULL);
		}

		else if (lifes == 1)
		{
			app->render->DrawTexture(FullHeartTex, 27, 16, false, &heart1, NULL);
			app->render->DrawTexture(EmptyHeartTex, 80, 16, false, &heart2, NULL);
			app->render->DrawTexture(EmptyHeartTex, 133, 16, false, &heart3, NULL);
			app->render->DrawTexture(EmptyHeartTex, 186, 16, false, &heart3, NULL);
			app->render->DrawTexture(EmptyHeartTex, 239, 16, false, &heart3, NULL);
		}

		else if (lifes == 0)
		{
			app->render->DrawTexture(EmptyHeartTex, 27, 16, false, &heart1, NULL);
			app->render->DrawTexture(EmptyHeartTex, 80, 16, false, &heart2, NULL);
			app->render->DrawTexture(EmptyHeartTex, 133, 16, false, &heart3, NULL);
			app->render->DrawTexture(EmptyHeartTex, 186, 16, false, &heart3, NULL);
			app->render->DrawTexture(EmptyHeartTex, 239, 16, false, &heart3, NULL);

			app->play->playerData.isDead = true;
		}

		app->render->DrawTexture(InventoryTex, 677, 8, false, &inventory, NULL);

		switch (soulCounter)
		{
		case 0:
			break;
		case 1:
			app->render->DrawTexture(DarkSoul, 733, 34, false, &soul1, NULL);
			break;

		case 2:
			app->render->DrawTexture(DarkSoul, 733, 34, false, &soul1, NULL);
			app->render->DrawTexture(DarkSoul, 760, 34, false, &soul2, NULL);
			break;
		case 3:
			app->render->DrawTexture(DarkSoul, 733, 34, false, &soul1, NULL);
			app->render->DrawTexture(DarkSoul, 760, 34, false, &soul2, NULL);
			app->render->DrawTexture(DarkSoul, 787, 34, false, &soul3, NULL);
			break;
		case 4:
			app->render->DrawTexture(DarkSoul, 733, 34, false, &soul1, NULL);
			app->render->DrawTexture(DarkSoul, 760, 34, false, &soul2, NULL);
			app->render->DrawTexture(DarkSoul, 787, 34, false, &soul3, NULL);
			app->render->DrawTexture(DarkSoul, 814, 34, false, &soul4, NULL);
			break;
		case 5:
			app->render->DrawTexture(DarkSoul, 733, 34, false, &soul1, NULL);
			app->render->DrawTexture(DarkSoul, 760, 34, false, &soul2, NULL);
			app->render->DrawTexture(DarkSoul, 787, 34, false, &soul3, NULL);
			app->render->DrawTexture(DarkSoul, 814, 34, false, &soul4, NULL);
			app->render->DrawTexture(DarkSoul, 841, 34, false, &soul5, NULL);
			break;
		case 6:
			app->render->DrawTexture(DarkSoul, 733, 34, false, &soul1, NULL);
			app->render->DrawTexture(DarkSoul, 760, 34, false, &soul2, NULL);
			app->render->DrawTexture(DarkSoul, 787, 34, false, &soul3, NULL);
			app->render->DrawTexture(DarkSoul, 814, 34, false, &soul4, NULL);
			app->render->DrawTexture(DarkSoul, 841, 34, false, &soul5, NULL);
			app->render->DrawTexture(DarkSoul, 868, 34, false, &soul6, NULL);
			break;
		default:
			break;
		}
	}
	

	return true;
}

void  ModuleHUD::Reset()
{
	lifes = 5;
	
}

bool ModuleHUD::CleanUp()
{
	bool ret;

	app->tex->CleanUp();
	app->font->UnLoad(GameFont);

	return true;
}

void ModuleHUD::DrawPauseMenu()
{
	app->render->DrawRectangle({ 100,160,440,270 }, 0, 0, 0, 175);

}
