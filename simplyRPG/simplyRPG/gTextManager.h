/*	This file is part of GEngine.
*
*Decription:
*
*Author: George Popov
*Date:
*Current Phase:
*/
#ifndef GTEXT_H
#define GTEXT_H

#include <SDL.h>
#include <map>
#include <string>
#include "gFont.h"
#include "gErrors.h"

using namespace std;

class gTextManager
{
public:
	gTextManager(void);
	~gTextManager(void);
	
	void init();
	
	//LOAD methods
	void loadCharMap();

	//Render methods
	void drawText(const char* text, gFont font, int x = 0, int y = 0);

private:
	SDL_Texture* map_texture;
	static map<char, int> char_map;//Contains ASCII charset
};

#endif