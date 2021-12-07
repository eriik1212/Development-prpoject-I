#ifndef __LEVEL2_H__
#define __LEVEL2_H__

#include "Module.h"
#include "Animation.h"
#include "Render.h"

struct SDL_Texture;


class Level2 : public Module
{
public:

	Level2(bool enabled);

	// Destructor
	virtual ~Level2();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// The wall/floor's collider
	Collider* wallCollider = nullptr;

	// scrollingOffset for Parallax Effect
	int scrollingOffset = 0;
private:

};
#endif // __LEVEL2_H__

