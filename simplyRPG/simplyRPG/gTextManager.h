#pragma once
#include "gFont.h"
#include "gErrors.h"
#include <SDL.h>
#include <map>
#include <string>

using namespace std;
class gTextManager
{
public:
	gTextManager(void);
	~gTextManager(void);

	void loadCharMap();
	void init();
	void drawText(const char* text, gFont font, int x = 0, int y = 0);

private:
	SDL_Texture* map_texture;
	static map<char, int> char_map;
};

