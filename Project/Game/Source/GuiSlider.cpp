#include "GuiSlider.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "Log.h"
#include "Window.h"
#include "TitleScreen.h"
#include "HUD.h"

GuiSlider::GuiSlider(uint32 id, SDL_Rect bounds, SDL_Rect sliderbarBounds, const char* text) : GuiControl(GuiControlType::SLIDER, id)
{
	//this->bounds = bounds;
	this->bounds.x = bounds.x * app->win->GetScale();
	this->bounds.y = bounds.y * app->win->GetScale();
	this->bounds.w = bounds.w * app->win->GetScale();
	this->bounds.h = bounds.h * app->win->GetScale();
	this->text = text;
	this->sliderbarBounds.x = sliderbarBounds.x * app->win->GetScale();
	this->sliderbarBounds.y = sliderbarBounds.y * app->win->GetScale();
	this->sliderbarBounds.w = sliderbarBounds.w * app->win->GetScale();
	this->sliderbarBounds.h = sliderbarBounds.h * app->win->GetScale();

	canClick = true;
	drawBasic = false;
}

GuiSlider::~GuiSlider()
{

}

bool GuiSlider::Update(float dt)
{
	if (state != GuiControlState::DISABLED)
	{
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);

		//LOG("X: %d, Y: %d", mouseX, mouseY);

		if ((mouseX > (sliderbarBounds.x) && (mouseX < ((sliderbarBounds.x + sliderbarBounds.w)))) &&
			(mouseY < (bounds.y + bounds.h) && mouseY > (bounds.y)))
		{
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
			{
				state = GuiControlState::NORMAL;
				NotifyObserver();
			}
		}
	}

	return false;
}

bool GuiSlider::Draw(Render* render)
{

	// Draw the right button depending on state
	switch (state)
	{

	case GuiControlState::DISABLED:
	{
		switch (id)
		{
		case 9:
			render->DrawRectangle(bounds, 0, 0, 0, 0);
			break;
		case 10:
			render->DrawRectangle(bounds, 0, 0, 0, 0);
			break;
		case 18:
			render->DrawRectangle(bounds, 0, 0, 0, 0);
			break;
		case 19:
			render->DrawRectangle(bounds, 0, 0, 0, 0);
			break;
		default:
			break;
		}
	} break;

	case GuiControlState::NORMAL:
	{
		//Checks the GUI element ID
		// ID = 9 -> Volume Slider
		// ID = 10 -> FX Slider

		// ID = 18 -> Volume Slider
		// ID = 19 -> FX Slider

		switch (id)
		{
		case 9:
			render->DrawRectangle(app->title->sliderVolRect, 255, 255, 255, 50);
			render->DrawRectangle(app->title->volumeRect, 255, 255, 255, 255);
			break;
		case 10:
			render->DrawRectangle(app->title->sliderFXRect, 255, 255, 255, 50);
			render->DrawRectangle(app->title->fxRect, 255, 255, 255, 255);
			break;
		case 18:
			render->DrawRectangle(app->hud->sliderVolRect, 255, 255, 255, 50, true, false);
			render->DrawRectangle(app->hud->volumeRect, 255, 255, 255, 255, true, false);
			break;
		case 19:
			render->DrawRectangle(app->hud->sliderFXRect, 255, 255, 255, 50, true, false);
			render->DrawRectangle(app->hud->fxRect, 255, 255, 255, 255, true, false);
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