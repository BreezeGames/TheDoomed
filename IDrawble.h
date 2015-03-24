#ifndef IDRAWBLE
#define IDRAWBLE

#include <SDL.h>
#include "gGraphicManager.h"

//Interface for all drawble objects
//MAIN superclass
//George Popov - 2014 (C)

class IDrawble
{
public:
	virtual void draw() = 0;
	virtual void remove() = 0;
	
	virtual bool load() = 0;
//virtual ~IDrawble(void);

protected:
	long int id;
	float x,y;
	SDL_Texture* default_texture;
};

#endif