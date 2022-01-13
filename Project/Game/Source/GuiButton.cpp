#include "GuiButton.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "Log.h"
#include "Window.h"
#include "TitleScreen.h"

GuiButton::GuiButton(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::BUTTON, id)
{
	//this->bounds = bounds;
	this->bounds.x = bounds.x * app->win->GetScale();
	this->bounds.y = bounds.y * app->win->GetScale();
	this->bounds.w = bounds.w * app->win->GetScale();
	this->bounds.h = bounds.h * app->win->GetScale();
	this->text = text;

	canClick = true;
	drawBasic = false;
}

GuiButton::~GuiButton()
{

}

bool GuiButton::Update(float dt)
{
	if (state != GuiControlState::DISABLED)
	{
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);

		//LOG("X: %d, Y: %d", mouseX, mouseY);

		if ((mouseX > (bounds.x) && (mouseX < ((bounds.x + bounds.w))) &&
			(mouseY > (bounds.y)) && (mouseY < (bounds.y + bounds.h))))
		{
			state = GuiControlState::FOCUSED;

			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
			{
				state = GuiControlState::PRESSED;
			}

			if (app->title->optionsEnabled && id != 5)
			{
				state = GuiControlState::DISABLED;

			}

			// If mouse button pressed -> Generate event!
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
			{
				NotifyObserver();
			}

		}
		else if (app->title->optionsEnabled && id != 5)
		{
			state = GuiControlState::DISABLED;

		}
		else state = GuiControlState::NORMAL;
	}
	else
	{
		if (!app->title->optionsEnabled && id != 5 && state == GuiControlState::DISABLED)
		{
			state = GuiControlState::NORMAL;

		}
	}

	return false;
}

bool GuiButton::Draw(Render* render)
{

	// Draw the right button depending on state
	switch (state)
	{

	case GuiControlState::DISABLED:
	{
		switch (id)
		{
		case 1:
			render->DrawRectangle(bounds, 0, 0, 0, 0);

		case 2:
			render->DrawRectangle(bounds, 0, 0, 0, 0);

			break;
		case 3:
			render->DrawRectangle(bounds, 0, 0, 0, 0);

			break;
		case 4:
			render->DrawRectangle(bounds, 0, 0, 0, 0);

			break;
		case 5:
			render->DrawRectangle(bounds, 0, 0, 0, 0);
			break;
		case 6:
			render->DrawRectangle(bounds, 0, 0, 0, 0);
			break;
		default:
			break;
		}
	} break;

	case GuiControlState::NORMAL:
	{
		//Checks the GUI element ID
		// ID = 1 -> New Game Button
		// ID = 2 -> Continue Button
		// ID = 3 -> Settings Button
		// ID = 4 -> Credits Button
		// ID = 5 -> ExitOptions Button
		// ID = 6 -> ExitGAME Button

		switch (id)
		{
		case 1:
			render->DrawTexture(app->title->NewGameUnpressed, bounds.x, bounds.y, false, 0);
			selectedSound_isPlaying = false;
			break;
		case 2:
			render->DrawTexture(app->title->ContinueUnpressed, bounds.x, bounds.y, false, 0);
			selectedSound_isPlaying = false;
			break;
		case 3:
			render->DrawTexture(app->title->settingsUnpressed, bounds.x, bounds.y, false, 0);
			selectedSound_isPlaying = false;
			break;
		case 4:
			render->DrawTexture(app->title->creditsUnpressed, bounds.x, bounds.y, false, 0);
			selectedSound_isPlaying = false;
			break;
		case 5:
			render->DrawTexture(app->title->exitOptions, bounds.x, bounds.y, false, 0);
			selectedSound_isPlaying = false;
			break;
		case 6:
			render->DrawTexture(app->title->exitGameUnpressed, bounds.x, bounds.y, false, 0);
			selectedSound_isPlaying = false;
			break;
		default:
			break;
		}

	} break;

	case GuiControlState::FOCUSED:
	{
		//Checks the GUI element ID
		// ID = 1 -> New Game Button
		// ID = 2 -> Continue Button
		// ID = 3 -> Settings Button
		// ID = 4 -> Credits Button
		// ID = 5 -> ExitOptions Button
		// ID = 6 -> ExitGame Button

		switch (id)
		{
		case 1:
			render->DrawTexture(app->title->NewGameUnpressed, bounds.x, bounds.y, false, 0);
			render->DrawTexture(app->title->SelectArrow, bounds.x - 40, bounds.y, false, 0);

			if (!selectedSound_isPlaying)
			{
				app->audio->PlayFx(app->title->changeFX);
				selectedSound_isPlaying = true;
			}
			break;
		case 2:
			render->DrawTexture(app->title->ContinueUnpressed, bounds.x, bounds.y, false, 0);
			render->DrawTexture(app->title->SelectArrow, bounds.x - 40, bounds.y, false, 0);

			if (!selectedSound_isPlaying)
			{
				app->audio->PlayFx(app->title->changeFX);
				selectedSound_isPlaying = true;
			}
			break;
		case 3:
			render->DrawTexture(app->title->settingsUnpressed, bounds.x, bounds.y, false, 0);
			render->DrawTexture(app->title->SelectArrow, bounds.x - 40, bounds.y, false, 0);

			if (!selectedSound_isPlaying)
			{
				app->audio->PlayFx(app->title->changeFX);
				selectedSound_isPlaying = true;
			}
			break;
		case 4:
			render->DrawTexture(app->title->creditsUnpressed, bounds.x, bounds.y, false, 0);
			render->DrawTexture(app->title->SelectArrow, bounds.x - 40, bounds.y, false, 0);

			if (!selectedSound_isPlaying)
			{
				app->audio->PlayFx(app->title->changeFX);
				selectedSound_isPlaying = true;
			}
			break;
		case 5:
			render->DrawTexture(app->title->exitOptionsFocused, bounds.x, bounds.y, false, 0);
			if (!selectedSound_isPlaying)
			{
				app->audio->PlayFx(app->title->changeFX);
				selectedSound_isPlaying = true;
			}
			
			break;
		case 6:
			render->DrawTexture(app->title->exitGameUnpressed, bounds.x, bounds.y, false, 0);
			render->DrawTexture(app->title->SelectArrow, bounds.x - 40, bounds.y, false, 0);

			if(!selectedSound_isPlaying)
			{
				app->audio->PlayFx(app->title->changeFX);
				selectedSound_isPlaying = true;
			}
			break;
		default:
			break;
		}

		//render->DrawRectangle(bounds, 255, 255, 255, 160);

	} break;
	case GuiControlState::PRESSED:
	{
		//Checks the GUI element ID
		// ID = 1 -> New Game Button
		// ID = 2 -> Continue Button
		// ID = 3 -> Settings Button
		// ID = 4 -> Credits Button
		// ID = 5 -> ExitOptions Button
		// ID = 6 -> ExitGame Button

		switch (id)
		{
		case 1:
			render->DrawTexture(app->title->NewGamePressed, bounds.x, bounds.y, false, 0);

			break;
		case 2:
			render->DrawTexture(app->title->ContinuePressed, bounds.x, bounds.y, false, 0);

			break;
		case 3:
			render->DrawTexture(app->title->settingsPressed, bounds.x, bounds.y, false, 0);

			break;
		case 4:
			render->DrawTexture(app->title->creditsPressed, bounds.x, bounds.y, false, 0);

			break;
		case 5:
			render->DrawTexture(app->title->exitOptionsPressed, bounds.x, bounds.y, false, 0);
			break;
		case 6:
			render->DrawTexture(app->title->exitGamePressed, bounds.x, bounds.y, false, 0);

			break;
		default:
			break;
		}

		//render->DrawRectangle(bounds, 255, 255, 255, 255);

	} break;
	case GuiControlState::BLOCKED:
	{
		switch (id)
		{
		case 2:
			render->DrawRectangle(bounds, 0, 255, 0, 255);
			break;
		default:
			break;
		}
	}
		break;

	default:
		break;
	}

	return false;
}