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
#include "TitleScreen.h"
#include "GuiManager.h"
#include "FadeToBlack.h"
#include "Map.h"
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

	resumeRect.x = 270;
	resumeRect.y = 220;
	resumeRect.w = 140;
	resumeRect.h = 16;

	titleRect.x = 270;
	titleRect.y = 260;
	titleRect.w = 140;
	titleRect.h = 16;

	exitRect.x = 300;
	exitRect.y = 340;
	exitRect.w = 40;
	exitRect.h = 16;

	settingsRect.x = 288;
	settingsRect.y = 300;
	settingsRect.w = 80;
	settingsRect.h = 16;

	exitOptionsRect.x = 125;
	exitOptionsRect.y = 185;
	exitOptionsRect.w = 16;
	exitOptionsRect.h = 16;

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
	volumeRect.x = sliderVolRect.x + 128 - volumeRect.w / 2;
	volumeRect.y = sliderVolRect.y - volumeRect.w / 2;

	fxRect.w = 16;
	fxRect.h = 16;
	fxRect.x = sliderFXRect.x + 128 - fxRect.w / 2;
	fxRect.y = sliderFXRect.y - fxRect.w / 2;
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

	exitOptions = app->tex->Load("Assets/textures/x.png");
	exitOptionsFocused = app->tex->Load("Assets/textures/xFocused.png");
	exitOptionsPressed = app->tex->Load("Assets/textures/xPressed.png");

	SelectArrow = app->tex->Load("Assets/textures/buttons/SelectedArrow.png");

	settingsUnpressed = app->tex->Load("Assets/textures/buttons/settingsUnpressed.png");
	settingsPressed = app->tex->Load("Assets/textures/buttons/settingsPressed.png");

	exitGameUnpressed = app->tex->Load("Assets/textures/buttons/exitGame.png");
	exitGamePressed = app->tex->Load("Assets/textures/buttons/exitGamePressed.png");

	titleUnpressed = app->tex->Load("Assets/textures/buttons/backToTitleUnpressed.png");
	titlePressed = app->tex->Load("Assets/textures/buttons/backToTitlePressed.png");

	resumeUnpressed = app->tex->Load("Assets/textures/buttons/resumeUnpressed.png");
	resumePressed = app->tex->Load("Assets/textures/buttons/resumePressed.png");

	resumeButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 11, "ResumeButton", resumeRect, this);
	titleButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 12, "TitleButton", titleRect, this);
	exitButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 13, "ExitButton", exitRect, this);
	settingsButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 14, "SettingsButton", settingsRect, this);

	exitOptionsButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 15, "ExitOptions", exitOptionsRect, this);

	fullscreenToggle = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::TOGGLE, 16, "FullscreenButton", fullscreenRect, this);
	vsyncToggle = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::TOGGLE, 17, "VsyncButton", vsyncRect, this);

	volumeSlider = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 18, "SliderVolume", volumeRect, this, sliderVolRect);
	fxSlider = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 19, "SliderFX", fxRect, this, sliderFXRect);

	resumeButton->state = GuiControlState::DISABLED;
	titleButton->state = GuiControlState::DISABLED;
	exitButton->state = GuiControlState::DISABLED;
	settingsButton->state = GuiControlState::DISABLED;
	fullscreenToggle->state = GuiControlState::DISABLED;
	vsyncToggle->state = GuiControlState::DISABLED;
	volumeSlider->state = GuiControlState::DISABLED;
	fxSlider->state = GuiControlState::DISABLED;

	exitOptionsButton->state = GuiControlState::DISABLED;

	return ret;
}

bool ModuleHUD::Update(float dt)
{
	if (exitGameRequest)
	{
		return false;
	}

	if (app->render->vsync) vsyncToggle->isOn = true;
	else vsyncToggle->isOn = false;

	if (app->win->fullscreen) fullscreenToggle->isOn = true;
	else fullscreenToggle->isOn = false;

	return true;
}

// Update: draw background
bool ModuleHUD::PostUpdate()
{

	if (app->scene->Enabled() || app->level2->Enabled())
	{

		if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && !pauseEnabled)
		{
			resumeButton->state = GuiControlState::NORMAL;
			titleButton->state = GuiControlState::NORMAL;
			exitButton->state = GuiControlState::NORMAL;
			settingsButton->state = GuiControlState::NORMAL;

			pauseEnabled = true;
			optionsEnabled = false;
		}
		else if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && pauseEnabled)
		{
			resumeButton->state = GuiControlState::DISABLED;
			titleButton->state = GuiControlState::DISABLED;
			exitButton->state = GuiControlState::DISABLED;
			settingsButton->state = GuiControlState::DISABLED;
			exitOptionsButton->state = GuiControlState::DISABLED;
			fullscreenToggle->state = GuiControlState::DISABLED;
			vsyncToggle->state = GuiControlState::DISABLED;
			volumeSlider->state = GuiControlState::DISABLED;
			fxSlider->state = GuiControlState::DISABLED;

			pauseEnabled = false;
			optionsEnabled = false;

		}
		else if (!pauseEnabled)
		{
			resumeButton->state = GuiControlState::DISABLED;
			titleButton->state = GuiControlState::DISABLED;
			exitButton->state = GuiControlState::DISABLED;
			settingsButton->state = GuiControlState::DISABLED;
		}
		else if (!optionsEnabled)
		{
			exitOptionsButton->state = GuiControlState::DISABLED;
			fullscreenToggle->state = GuiControlState::DISABLED;
			vsyncToggle->state = GuiControlState::DISABLED;
			volumeSlider->state = GuiControlState::DISABLED;
			fxSlider->state = GuiControlState::DISABLED;
		}
		else if (!pauseEnabled && !optionsEnabled)
		{
			resumeButton->state = GuiControlState::DISABLED;
			titleButton->state = GuiControlState::DISABLED;
			exitButton->state = GuiControlState::DISABLED;
			settingsButton->state = GuiControlState::DISABLED;
			exitOptionsButton->state = GuiControlState::DISABLED;
			fullscreenToggle->state = GuiControlState::DISABLED;
			vsyncToggle->state = GuiControlState::DISABLED;
			volumeSlider->state = GuiControlState::DISABLED;
			fxSlider->state = GuiControlState::DISABLED;
		}
		
		if (pauseEnabled)
		{
			DrawPauseMenu();

		}

		if (optionsEnabled)
		{
			app->title->DrawOptionsMenu();
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
	
	if (app->title->Disabled())
	{
		//Draw GUI
		app->guiManager->Draw();
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
	app->render->DrawRectangle({ 100,160,440,270 }, 255, 255, 255, 175, true, false);

}

bool ModuleHUD::OnGuiMouseClickEvent(GuiControl* control)
{

	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID
		// ID = 11 -> ResumeGame Button
		// ID = 12 -> TitleGame Button
		// ID = 15 -> ExitOptionsGame Button

		switch (control->id)
		{
		case 11:
			app->audio->PlayFx(app->title->enterFX);

			pauseEnabled = false;
			break;
		case 12:
			app->audio->PlayFx(app->title->enterFX);

			exitOptionsButton->state = GuiControlState::DISABLED;
			resumeButton->state = GuiControlState::DISABLED;
			titleButton->state = GuiControlState::DISABLED;
			exitButton->state = GuiControlState::DISABLED;
			settingsButton->state = GuiControlState::DISABLED;
			fullscreenToggle->state = GuiControlState::DISABLED;
			vsyncToggle->state = GuiControlState::DISABLED;
			volumeSlider->state = GuiControlState::DISABLED;
			fxSlider->state = GuiControlState::DISABLED;

			app->fade->FadeToBlack(this, app->title, 30);

			//Disable Player & map
			app->play->Disable();
			app->map->Disable();
			app->level2->Disable();
			app->scene->Disable();
			app->enemies->Disable();
			app->hud->Disable();
			break;
		case 13:
			app->audio->PlayFx(app->title->enterFX);

			exitGameRequest = true;
			break;
		case 14:
			app->audio->PlayFx(app->title->enterFX);

			optionsEnabled = true;
			pauseEnabled = false;

			exitOptionsButton->state = GuiControlState::NORMAL;
			fullscreenToggle->state = GuiControlState::NORMAL;
			vsyncToggle->state = GuiControlState::NORMAL;
			volumeSlider->state = GuiControlState::NORMAL;
			fxSlider->state = GuiControlState::NORMAL;

			break;
		case 15:
			app->audio->PlayFx(app->title->enterFX);

			if (optionsEnabled) optionsEnabled = false;
			pauseEnabled = true;

			exitOptionsButton->state = GuiControlState::DISABLED;
			resumeButton->state = GuiControlState::NORMAL;
			titleButton->state = GuiControlState::NORMAL;
			exitButton->state = GuiControlState::NORMAL;
			settingsButton->state = GuiControlState::NORMAL;
			fullscreenToggle->state = GuiControlState::DISABLED;
			vsyncToggle->state = GuiControlState::DISABLED;
			volumeSlider->state = GuiControlState::DISABLED;
			fxSlider->state = GuiControlState::DISABLED;

			break;
		}

	default: break;
	}
	case GuiControlType::TOGGLE:
		switch (control->id)
		{
		case 16:
			app->audio->PlayFx(app->title->enterFX);

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
		case 17:
			app->audio->PlayFx(app->title->enterFX);

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
		case 18:
			//LOG("sliderRectX: %d, sliderRectW+X: %d", sliderVolRect.x, sliderVolRect.x + sliderVolRect.w);
			//LOG("mouseX: %d, mouseY: %d", mouseX, mouseY);
			int volume;

			volumeRect.x = mouseX;

			volume = volumeRect.x - 240;

			app->audio->SetVolume(volume);

			break;
		case 19:
			//LOG("sliderRectX: %d, sliderRectW+X: %d", sliderVolRect.x, sliderVolRect.x + sliderVolRect.w);
			//LOG("mouseX: %d, mouseY: %d", mouseX, mouseY);

			int volumeFX;

			fxRect.x = mouseX;

			volumeFX = fxRect.x - 240;

			app->audio->SetVolumeFX(app->title->changeFX, volumeFX);
			app->audio->SetVolumeFX(app->title->enterFX, volumeFX);

			break;
		}

	}
	return true;
}