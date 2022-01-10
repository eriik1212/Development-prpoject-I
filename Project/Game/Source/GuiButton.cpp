#include "GuiButton.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "Log.h"
#include "Window.h"
#include "TitleScreen.h"

GuiButton::GuiButton(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::BUTTON, id)
{
	this->bounds = bounds;
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

		LOG("X: %d, Y: %d", mouseX, mouseY);

		if ((mouseX > (bounds.x * app->win->GetScale()) && (mouseX < ((bounds.x + bounds.w) * app->win->GetScale())) &&
			(mouseY > (bounds.y * app->win->GetScale())) && (mouseY < ((bounds.y + bounds.h) * app->win->GetScale()))))
		{
			state = GuiControlState::FOCUSED;

			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
			{
				state = GuiControlState::PRESSED;
			}

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

bool GuiButton::Draw(Render* render)
{

	// Draw the right button depending on state
	switch (state)
	{

	case GuiControlState::DISABLED:
	{
		render->DrawRectangle(bounds, 0, 0, 0, 0);
	} break;

	case GuiControlState::NORMAL:
	{
		//Checks the GUI element ID
		if (id == 1)
		{
			app->render->DrawTexture(app->title->NewGameUnpressed, bounds.x, bounds.y, true, &app->title->NewGameRect);

		}

		if (id == 2)
		{
			
		}

		render->DrawRectangle(bounds, 255, 0, 0, 255);

	} break;

	case GuiControlState::FOCUSED:
	{
		render->DrawRectangle(bounds, 255, 255, 255, 160);
	} break;
	case GuiControlState::PRESSED:
	{
		render->DrawRectangle(bounds, 255, 255, 255, 255);
	} break;

	/******/

	case GuiControlState::SELECTED: render->DrawRectangle(bounds, 0, 255, 0, 255);
		break;

	default:
		break;
	}

	return false;
}