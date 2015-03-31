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
	IDrawble() {coords.x = coords.y = 0; 
				size.x = size.y = 0;
				id = 0;}

	virtual void draw() = 0;
	virtual void remove() = 0;
	
	virtual bool load() = 0;
protected:
	//GetFunctions
	int getX() const{ return coords.x; }
	int getY() const{ return coords.y; }
	int getSizeX() const{ return size.x; }
	int getSizeY() const{ return size.y; }
	long int getID() const{ return id; }

	//SetFunctions
	void setX(int dx){ size.x = dx; }
	void setY(int dy){ size.y = dy; }

protected:
	long int id;
	SDL_Point coords;
	SDL_Point size;
	SDL_Texture* default_texture;
};

#endif