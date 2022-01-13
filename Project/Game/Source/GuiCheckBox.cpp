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
	isOn = false;
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
			// If mouse button pressed -> Generate event!
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
			{
				NotifyObserver();
			}

		}
		else state = GuiControlState::NORMAL;
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
			render->DrawRectangle(app->title->fullscreenRect, 255, 255, 255, 100);
			selectedSound_isPlaying = false;

			if (isOn)
			{
				render->DrawRectangle({ app->title->fullscreenRect.x + 2, app->title->fullscreenRect.y + 2, app->title->fullscreenRect.w - 4, app->title->fullscreenRect.h - 4 }, 255, 255, 255, 255);
			}

			break;
		case 8:
			render->DrawRectangle(app->title->vsyncRect, 255, 255, 255, 100);
			selectedSound_isPlaying = false;

			if (isOn)
			{
				render->DrawRectangle({ app->title->vsyncRect.x + 2, app->title->vsyncRect.y + 2, app->title->vsyncRect.w - 4, app->title->vsyncRect.h - 4 }, 255, 255, 255, 255);
			}

			break;
		default:
			break;
		}

	} break;
	default:
		break;

	

	return false;
	}
}