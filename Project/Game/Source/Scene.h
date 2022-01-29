#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Animation.h"
#include "Render.h"
#include "Item.h"

struct SDL_Texture;


class Scene : public Module
{
public:

	Scene(bool enabled);

	// Destructor
	virtual ~Scene();

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

	int minutes = 0;

	char textMinutes[10] = { "\0" };
	char textPoints[10] = { "\0" };
private:
	
	SDL_Texture* background_sky;
	SDL_Texture* background_middlemountain;
	SDL_Texture* background_middlecloud;
	SDL_Texture* background_grass;
	SDL_Texture* background_frontmountain;
	SDL_Texture* background_frontcloud;
	SDL_Texture* background_backmountain;
	SDL_Texture* background_backcloud;
	SDL_Texture* greenFlagLVL1;
	SDL_Texture* redFlagLVL1;

	Item* item1;
	Item* item2;
	Item* item3;
};
#endif // __SCENE_H__