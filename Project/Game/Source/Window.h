#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "Module.h"

#include "App.h"

#include "Defs.h"
#include "Log.h"

struct SDL_Window;
struct SDL_Surface;

class Window : public Module
{
public:

	Window(bool enabled);

	// Destructor
	virtual ~Window();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called at the middle of the application loop
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

	// Changae title
	void SetTitle(const char* title);

	// Retrive window size
	void GetWindowSize(uint& width, uint& height) const;

	// Retrieve window scale
	float GetScale() const;

	// Retrieve window Width
	int GetWidth() const;

	// Retrieve window height
	int GetHeight() const;

public:
	// The window we'll be rendering to
	SDL_Window* window;

	// The surface contained by the window
	SDL_Surface* screenSurface;

	int width;
	int height;
	float scale;

	int flags;
	bool fullscreen = false;
	bool borderless = false;
	bool resizable = false;
	bool fullscreen_window = false;

private:
	SString title;

};

#endif // __WINDOW_H__