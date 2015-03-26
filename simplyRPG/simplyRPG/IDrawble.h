/*	This file is part of GEngine.
*
*Decription:
*
*Author: George Popov
*Date:
*Current Phase:
*/
#ifndef IDRAWBLE
#define IDRAWBLE

#include <SDL.h>
#include "gGraphicManager.h"

class IDrawble
{
public:
	virtual void draw() = 0;
	virtual void remove() = 0;
	
	virtual bool load() = 0;

protected:
	long int id;
	float x,y;
	SDL_Texture* default_texture;
};

#endif