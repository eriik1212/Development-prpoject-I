#include "TitleScreen.h"

#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Audio.h"
#include "Input.h"
#include "Map.h"
#include "Player.h"
#include "FadeToBlack.h"


TitleScreen::TitleScreen(bool enabled) : Module(enabled)
{

}

TitleScreen::~TitleScreen()
{

}

// Load assets
bool TitleScreen::Start()
{
	//TitleMusic = app->play->("Assets/audio/fx/game_over.wav");

	if (this->Enabled())
	{
		// Load music
		app->audio->PlayMusic("Assets/audio/music/title_music.ogg");

		//load textures
		
		

		
		
	}
	changeFX = app->audio->LoadFx("Assets/audio/fx/switching.wav");
	enterFX = app->audio->LoadFx("Assets/audio/fx/enter.wav");

	Title = app->tex->Load("Assets/textures/titleW.png");
	NewGamePressed= app->tex->Load("Assets/textures/PressedNG.png");
	NewGameUnpressed= app->tex->Load("Assets/textures/UnpressedNG.png");
	ContinuePressed= app->tex->Load("Assets/textures/PressedCont.png");
	ContinueUnpressed= app->tex->Load("Assets/textures/UnpressedContP.png");

	app->render->camera.x = 0;
	app->render->camera.y = 0;

	NewGameRect.x = 0;
	NewGameRect.y = 0;
	NewGameRect.w = 99;
	NewGameRect.h = 16;

	ContinueRect.x = 0;
	ContinueRect.y = 0;
	ContinueRect.w = 152;
	ContinueRect.h = 16;

	backgroundTitle.x = 0;
	backgroundTitle.y = 0;
	backgroundTitle.w = 690;
	backgroundTitle.h = 480;
	// Members Texture
	//GameOverTex = app->tex->Load("Assets/textures/gameover.png");

	//Aqui podem posar algun so a veure amb la pantalla d'inici
	//app->audio->PlayMusic("Assets/Audio/02_character_selection.ogg", 1.0f);

	//Fade In
	//app->fade->FadeToBlack(this, app->gameOver, 30);

	return true;
}

bool TitleScreen::Update(float dt)
{
	// ScanCodes
	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		//Fade Out
		app->audio->PlayFx(enterFX);
		if (option == 1)//New game option
		{
			cont = false;
			app->fade->FadeToBlack(this, app->scene, 30);
			
			app->play->playerData.isDead = false;
			

		}
		else //continue option
		{
			/*cont = true;
			app->fade->FadeToBlack(this, app->scene, 30);*/
		}
		
		
	}

	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		app->audio->PlayFx(changeFX);
		option = 0;
	}

	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
	{
		app->audio->PlayFx(changeFX);
		option = 1;
	}

	

	else if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		return false;
	}

	return true;
}

// Update: draw background
bool TitleScreen::PostUpdate()
{

	app->render->DrawTexture(Title, 0, 0, NULL);
	if (option == 1)
	{
		app->render->DrawTexture(NewGamePressed, 271, 280, &NewGameRect);
		app->render->DrawTexture(ContinueUnpressed, 246, 307, &ContinueRect);
	}
	else
	{
		app->render->DrawTexture(NewGameUnpressed, 271, 280, &NewGameRect);
		app->render->DrawTexture(ContinuePressed, 246, 307, &ContinueRect);
	}
	
	//app->render->DrawTexture(nom textura, rectangle.x, rectangle.y, &rectangle)
	return true;
}