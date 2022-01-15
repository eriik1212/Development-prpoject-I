#include "TitleScreen.h"

#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Audio.h"
#include "Input.h"
#include "Map.h"
#include "Player.h"
#include "FadeToBlack.h"
#include "Level2.h"
#include "GuiManager.h"
#include "Window.h"
#include "Font.h"
#include "HUD.h"

#include "Defs.h"
#include "Log.h"


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

		//Disable Player & map
		app->play->Disable();
		app->map->Disable();
		app->hud->Enable();

		app->LoadGameRequest();
		//app->LoadInitialGameRequest();

	}
	changeFX = app->audio->LoadFx("Assets/audio/fx/switching.wav");
	enterFX = app->audio->LoadFx("Assets/audio/fx/enter.wav");

	Title = app->tex->Load("Assets/textures/titleW.png");

	NewGamePressed= app->tex->Load("Assets/textures/buttons/PressedNG.png");
	NewGameUnpressed= app->tex->Load("Assets/textures/buttons/UnpressedNG.png");
	ContinuePressed= app->tex->Load("Assets/textures/buttons/PressedCont.png");
	ContinueUnpressed= app->tex->Load("Assets/textures/buttons/UnpressedCont.png");
	exitGameUnpressed= app->tex->Load("Assets/textures/buttons/exitGame.png");
	exitGamePressed= app->tex->Load("Assets/textures/buttons/exitGamePressed.png");
	settingsUnpressed= app->tex->Load("Assets/textures/buttons/settingsUnpressed.png");
	settingsPressed= app->tex->Load("Assets/textures/buttons/settingsPressed.png");
	creditsUnpressed= app->tex->Load("Assets/textures/buttons/creditsUnpressed.png");
	creditsPressed= app->tex->Load("Assets/textures/buttons/creditsPressed.png");
	exitOptions= app->tex->Load("Assets/textures/x.png");
	exitOptionsFocused= app->tex->Load("Assets/textures/xFocused.png");
	exitOptionsPressed= app->tex->Load("Assets/textures/xPressed.png");
	SelectArrow = app->tex->Load("Assets/textures/buttons/SelectedArrow.png");

	app->render->camera.x = 0;
	app->render->camera.y = 0;

	NewGameRect.x = 288;
	NewGameRect.y = 260;
	NewGameRect.w = 80;
	NewGameRect.h = 16;

	ContinueRect.x = 276;
	ContinueRect.y = 280;
	ContinueRect.w = 124;
	ContinueRect.h = 16;

	settingsRect.x = 288;
	settingsRect.y = 300;
	settingsRect.w = 80;
	settingsRect.h = 16;

	creditsRect.x = 288;
	creditsRect.y = 320;
	creditsRect.w = 80;
	creditsRect.h = 16;

	fullscreenRect.x = 388;
	fullscreenRect.y = 340;
	fullscreenRect.w = 16;
	fullscreenRect.h = 16;

	vsyncRect.x = 388;
	vsyncRect.y = 380;
	vsyncRect.w = 16;
	vsyncRect.h = 16;

	sliderVolRect.x = 240;
	sliderVolRect.y = 230;
	sliderVolRect.w = 128;
	sliderVolRect.h = 6;

	sliderFXRect.x = 240;
	sliderFXRect.y = 300;
	sliderFXRect.w = 128;
	sliderFXRect.h = 6;

	volumeRect.w = 16;
	volumeRect.h = 16;
	volumeRect.x = sliderVolRect.x + 128 - volumeRect.w/2;
	volumeRect.y = sliderVolRect.y - volumeRect.w/2;

	fxRect.w = 16;
	fxRect.h = 16;
	fxRect.x = sliderFXRect.x + 128 - fxRect.w / 2;
	fxRect.y = sliderFXRect.y - fxRect.w / 2;

	exitGameRect.x = 300;
	exitGameRect.y = 340;
	exitGameRect.w = 40;
	exitGameRect.h = 16;

	exitOptionsRect.x = 125;
	exitOptionsRect.y = 185;
	exitOptionsRect.w = 16;
	exitOptionsRect.h = 16;

	backgroundTitle.x = 0;
	backgroundTitle.y = 0;
	backgroundTitle.w = 690;
	backgroundTitle.h = 480;

	exitGameRequest = false;

	newGameButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "NewGame", NewGameRect, this);
	continueButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Continue", ContinueRect, this);
	settingsButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Settings", settingsRect, this);
	creditsButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "Credits", creditsRect, this);
	exitOptionsButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "ExitOptions", exitOptionsRect, this);
	exitGameButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "ExitGame", exitGameRect, this);

	fullscreenToggle = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::TOGGLE, 7, "FullscreenButton", fullscreenRect, this);
	vsyncToggle = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::TOGGLE, 8, "VsyncButton", vsyncRect, this);

	volumeSlider = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 9, "SliderVolume", volumeRect, this, sliderVolRect);
	fxSlider = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 10, "SliderFX", fxRect, this, sliderFXRect);
	
	exitOptionsButton->state = GuiControlState::DISABLED;
	fullscreenToggle->state = GuiControlState::DISABLED;
	vsyncToggle->state = GuiControlState::DISABLED;

	volumeSlider->state = GuiControlState::DISABLED;
	fxSlider->state = GuiControlState::DISABLED;

	newGameButton->state = GuiControlState::NORMAL;
	continueButton->state = GuiControlState::NORMAL;
	settingsButton->state = GuiControlState::NORMAL;
	creditsButton->state = GuiControlState::NORMAL;
	exitGameButton->state = GuiControlState::NORMAL;

	LOG("ENABLED");

	return true;
}

bool TitleScreen::Update(float dt)
{

	if (app->render->vsync) vsyncToggle->isOn = true;
	else vsyncToggle->isOn = false;

	if (app->win->fullscreen) fullscreenToggle->isOn = true;
	else fullscreenToggle->isOn = false;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || exitGameRequest)
	{
		return false;
	}

	return true;
}

// Update: draw background
bool TitleScreen::PostUpdate()
{

	app->render->DrawTexture(Title, 0, 0, false, NULL);

	if (optionsEnabled)
	{
		DrawOptionsMenu();
		
	}
	if (creditsEnabled)
	{
		DrawCreditsMenu();

	}

	//Draw GUI
	app->guiManager->Draw();

	// DrawTexture TEMPLATE
	//app->render->DrawTexture(nom textura, rectangle.x, rectangle.y, --necesita estar escalat?--, &rectangle)
	return true;
}

bool TitleScreen::CleanUp()
{
	LOG("Freeing TitleScreen");

	return true;
}

bool TitleScreen::OnGuiMouseClickEvent(GuiControl* control)
{

	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID
		// ID = 1 -> New Game Button
		// ID = 2 -> Continue Button
		// ID = 3 -> Settings Button
		// ID = 4 -> Credits Button
		// ID = 5 -> ExitOptions Button
		// ID = 6 -> ExitGame Button

		switch (control->id)
		{
		case 1:
			cont = false;

			app->font->UnLoad(app->hud->GameFont);
			app->hud->Disable();

			exitOptionsButton->state = GuiControlState::DISABLED;
			fullscreenToggle->state = GuiControlState::DISABLED;
			vsyncToggle->state = GuiControlState::DISABLED;
			newGameButton->state = GuiControlState::DISABLED;
			continueButton->state = GuiControlState::DISABLED;
			settingsButton->state = GuiControlState::DISABLED;
			creditsButton->state = GuiControlState::DISABLED;
			exitGameButton->state = GuiControlState::DISABLED;
			volumeSlider->state = GuiControlState::DISABLED;
			fxSlider->state = GuiControlState::DISABLED;

			app->audio->PlayFx(enterFX);

			app->play->restartLVL1 = true;
			//app->SaveGameRequest();
			app->fade->FadeToBlack(this, app->scene, 30);

			app->play->playerData.isDead = false;

			app->tex->CleanUp();

			LOG("Click on NewGame");
			break;
		case 2:
			cont = true;

			app->font->UnLoad(app->hud->GameFont);
			app->hud->Disable();

			exitOptionsButton->state = GuiControlState::DISABLED;
			fullscreenToggle->state = GuiControlState::DISABLED;
			vsyncToggle->state = GuiControlState::DISABLED;
			newGameButton->state = GuiControlState::DISABLED;
			continueButton->state = GuiControlState::DISABLED;
			settingsButton->state = GuiControlState::DISABLED;
			creditsButton->state = GuiControlState::DISABLED;
			exitGameButton->state = GuiControlState::DISABLED;
			volumeSlider->state = GuiControlState::DISABLED;
			fxSlider->state = GuiControlState::DISABLED;

			app->audio->PlayFx(enterFX);

			app->tex->CleanUp();

			if (app->play->lastLevel == 1)
			{
				app->fade->FadeToBlack(this, app->scene, 30);
				app->LoadGameRequest();

			}

			if (app->play->lastLevel == 2)
			{
				app->fade->FadeToBlack(this, app->level2, 30);
				app->LoadGameRequest();

			}

			LOG("Click on ContinueGame");
			break;
		case 3:
			app->audio->PlayFx(enterFX);

			optionsEnabled = true;

			exitOptionsButton->state = GuiControlState::NORMAL;
			fullscreenToggle->state = GuiControlState::NORMAL;
			vsyncToggle->state = GuiControlState::NORMAL;
			volumeSlider->state = GuiControlState::NORMAL;
			fxSlider->state = GuiControlState::NORMAL;

			LOG("DISABLED");

			break;
		case 4:
			app->audio->PlayFx(enterFX);

			creditsEnabled = true;

			exitOptionsButton->state = GuiControlState::NORMAL;

			break;
		case 5:
			app->audio->PlayFx(enterFX);

			if(optionsEnabled) optionsEnabled = false;
			if(creditsEnabled) creditsEnabled = false;

			exitOptionsButton->state = GuiControlState::DISABLED;
			fullscreenToggle->state = GuiControlState::DISABLED;
			vsyncToggle->state = GuiControlState::DISABLED;
			volumeSlider->state = GuiControlState::DISABLED;
			fxSlider->state = GuiControlState::DISABLED;

			newGameButton->state = GuiControlState::NORMAL;
			continueButton->state = GuiControlState::NORMAL;
			settingsButton->state = GuiControlState::NORMAL;
			creditsButton->state = GuiControlState::NORMAL;
			exitGameButton->state = GuiControlState::NORMAL;

			break;
		case 6:
			app->audio->PlayFx(enterFX);

			exitGameRequest = true;
			break;
		default:
			break;
		}

	}
	case GuiControlType::TOGGLE:
		switch (control->id)
		{
		case 7:
			app->audio->PlayFx(enterFX);

			if (!fullscreenToggle->isOn)
			{
				fullscreenToggle->isOn = true;
				app->win->fullscreen = true;
			}
			else
			{
				fullscreenToggle->isOn = false;
				app->win->fullscreen = false;
			}

			break;
		case 8:
			app->audio->PlayFx(enterFX);

			if (!vsyncToggle->isOn)
			{
				vsyncToggle->isOn = true;
				app->render->vsync = true;
			}
			else
			{
				vsyncToggle->isOn = false;
				app->render->vsync = false;
			}


			break;

		default:
			break;

		}

	case GuiControlType::SLIDER:
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);

		mouseX /= app->win->GetScale();

		switch (control->id)
		{
		case 9:
			//LOG("sliderRectX: %d, sliderRectW+X: %d", sliderVolRect.x, sliderVolRect.x + sliderVolRect.w);
			//LOG("mouseX: %d, mouseY: %d", mouseX, mouseY);
			int volume;

			volumeRect.x = mouseX;

			volume = volumeRect.x - 240;

			app->audio->SetVolume(volume);

			break;
		case 10:
			//LOG("sliderRectX: %d, sliderRectW+X: %d", sliderVolRect.x, sliderVolRect.x + sliderVolRect.w);
			//LOG("mouseX: %d, mouseY: %d", mouseX, mouseY);

			int volumeFX;

			fxRect.x = mouseX;

			volumeFX = fxRect.x - 240;
			
			app->audio->SetVolumeFX(changeFX, volumeFX);
			app->audio->SetVolumeFX(enterFX, volumeFX);

			break;
		}

	default: break;
	}

	return true;
}

void TitleScreen::DrawOptionsMenu()
{
	app->render->DrawRectangle({ 100,160,440,270 }, 0, 0, 0, 175, true, false);

	app->font->BlitText(360, 300, app->hud->GameFont, "MUSIC VOLUME");

	app->font->BlitText(380, 400, app->hud->GameFont, "FX VOLUME");

	app->font->BlitText(300, fullscreenRect.y * 1.5, app->hud->GameFont, "FULLSCREEN");

	app->font->BlitText(300, vsyncRect.y * 1.5, app->hud->GameFont, "VSYNC");
}

void TitleScreen::DrawCreditsMenu()
{
	app->render->DrawRectangle({ 100,160,440,270 }, 0, 0, 0, 175, true, false);

	app->font->BlitText(280,280, app->hud->GameFont, "UPC-CITM GDDV 2nd YEAR");

	app->font->BlitText(380,320, app->hud->GameFont, "GINUH GAMES");

	app->font->BlitText(200,360, app->hud->GameFont, "MEMBERS:");
	app->font->BlitText(200,400, app->hud->GameFont, "DAVID BOCES OBIS");
	app->font->BlitText(200,440, app->hud->GameFont, "ERIK MARTIN GARZON");

	app->font->BlitText(200,500, app->hud->GameFont, "TUTOR:");
	app->font->BlitText(200, 540, app->hud->GameFont, "PEDRO OMEDAS MORERA");

	app->font->BlitText(200, 600, app->hud->GameFont, "LICENSE:");
	app->font->BlitText(400, 600, app->hud->GameFont, "MIT LICENSE");


}
