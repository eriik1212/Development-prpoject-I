#ifndef __GUISLIDER_H__
#define __GUISLIDER_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiSlider : public GuiControl
{
public:

	GuiSlider(uint32 id, SDL_Rect bounds, SDL_Rect sliderbarBounds, const char* text);
	virtual ~GuiSlider();

	bool Update(float dt);
	bool Draw(Render* render);

	int mouseX, mouseY;
	unsigned int click;

	bool canClick = true;
	bool drawBasic = false;

	bool selectedSound_isPlaying = false;

private:
	SDL_Rect sliderbarBounds;
};

#endif // __GUISLIDER_H__