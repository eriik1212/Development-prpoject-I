#include "GuiCheckBox.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "Log.h"
#include "Window.h"
#include "TitleScreen.h"

GuiCheckBox::GuiCheckBox(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::TOGGLE, id)
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

GuiCheckBox::~GuiCheckBox()
{

}

bool GuiCheckBox::Update(float dt)
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

bool GuiCheckBox::Draw(Render* render)
{

	// Draw the right button depending on state
	switch (state)
	{

	case GuiControlState::DISABLED:
	{
		switch (id)
		{
		case 7:
			render->DrawRectangle(bounds, 0, 0, 0, 0);
			break;
		case 8:
			render->DrawRectangle(bounds, 0, 0, 0, 0);
			break;
		default:
			break;
		}
	} break;

	case GuiControlState::NORMAL:
	{
		//Checks the GUI element ID
		// ID = 7 -> Fullscreen Toggle
		// ID = 8 -> Vsync Toggle

		switch (id)
		{
		case 7:
			render->DrawRectangle(app->title->fullscreenRect, 0, 0, 0, 150);
			selectedSound_isPlaying = false;
			break;
		case 8:
			render->DrawRectangle(app->title->vsyncRect, 0, 0, 0, 150);
			selectedSound_isPlaying = false;
			break;
		default:
			break;
		}

	} break;

	case GuiControlState::FOCUSED:
	{
		//Checks the GUI element ID
		// ID = 7 -> Fullscreen Toggle
		// ID = 8 -> Vsync Toggle

		switch (id)
		{
		case 7:
			render->DrawRectangle(app->title->fullscreenRect, 0, 0, 0, 200);

			if (!selectedSound_isPlaying)
			{
				app->audio->PlayFx(app->title->changeFX);
				selectedSound_isPlaying = true;
			}
			break;
		case 8:
			render->DrawRectangle(app->title->vsyncRect, 0, 0, 0, 200);

			if (!selectedSound_isPlaying)
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
		// ID = 7 -> Fullscreen Toggle
		// ID = 8 -> Vsync Toggle

		switch (id)
		{
		case 7:
			render->DrawRectangle(app->title->fullscreenRect, 255, 255, 255, 200);

			break;
		case 8:
			render->DrawRectangle(app->title->vsyncRect, 255, 255, 255, 200);

			break;
		default:
			break;
		}

		//render->DrawRectangle(bounds, 255, 255, 255, 255);

	} break;
	case GuiControlState::BLOCKED:
	{
	default:
		break;
	}

	return false;
	}
}