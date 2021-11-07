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

	Title = app->tex->Load("Assets/textures/titleW.png");

	app->render->camera.x = 0;
	app->render->camera.y = 0;

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
		app->fade->FadeToBlack(this, app->scene, 30);
		app->play->revive = true;
		app->play->playerData.isDead = false;
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

	app->render->DrawRectangle(backgroundTitle, 255, 255, 255, 255);
	app->render->DrawTexture(Title, 0, 0, NULL);
	return true;
}