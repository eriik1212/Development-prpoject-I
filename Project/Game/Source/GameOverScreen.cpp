#include "GameOverScreen.h"

#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Audio.h"
#include "Input.h"
#include "Map.h"
#include "Player.h"
#include "FadeToBlack.h"


GameOverScreen::GameOverScreen(bool enabled) : Module(enabled)
{
	
}

GameOverScreen::~GameOverScreen()
{

}

// Load assets
bool GameOverScreen::Start()
{
	LostGameFX = app->audio->LoadFx("Assets/audio/fx/game_over.wav");
	if (this->Enabled())
	{
		// Load music
		app->audio->StopMusic();
		app->audio->PlayFx(LostGameFX);
		
		//Disable Player & map
		app->play->Disabled();
		app->map->Disabled();
		app->scene->Disabled();
	}
	app->render->camera.x = 0;
	app->render->camera.y = 0;

	

	// Members Texture
	GameOverTex = app->tex->Load("Assets/textures/gameover.png");

	//Aqui podem posar algun so a veure amb la pantalla d'inici
	//app->audio->PlayMusic("Assets/Audio/02_character_selection.ogg", 1.0f);

	//Fade In
	app->fade->FadeToBlack(this, app->gameOver, 30);

	return true;
}

bool GameOverScreen::Update(float dt)
{
	// ScanCodes
	if (app->input->GetKey(SDL_SCANCODE_RETURN) ==KEY_DOWN)
	{
		//Fade Out
		app->fade->FadeToBlack(this, app->scene, 30);
	}

	else if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		return false;
	}

	return true;
}

// Update: draw background
bool GameOverScreen::PostUpdate()
{

	
	app->render->DrawTexture(GameOverTex, 0, 0, NULL);
	return true;
}
