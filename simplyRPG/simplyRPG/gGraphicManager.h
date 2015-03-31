/*	This file is part of GEngine.
*
*Decription:
*
*Author: George Popov
*Date:
*Current Phase: In development
*/
#ifndef GGRAPHIC_H
#define GGRAPHIC_H

#include <SDL.h>
#include <iostream>
#include "gTextManager.h"

using namespace std;

class gGraphicManager
{
public:
	static gGraphicManager& getGraphicManager(); //Return an adress of last initialized graphic manager
	static SDL_Point getTextureSize(SDL_Texture* texture); // Return texture size in pixels

	gGraphicManager(const int width = 800,const int height = 600);
	~gGraphicManager(void);

	void UpdateScreen(const float dt = 0);

	//RENDER methods
	bool RenderTexture(SDL_Texture* texture, Uint8 flags = 0);
	bool RenderTexture(SDL_Texture* texture, SDL_Rect source, int x = 0, int y = 0, float scale = 1.0f);
	bool RenderTexture(SDL_Texture* texture, int x, int y, float scale = 1.0f, Uint8 flags = 0);

	//SET methods
	void setWindowFullScreen();
	void setRenderDrawColor(SDL_Color color);
	void setRenderDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0);

	//LOAD methods
	SDL_Texture* loadTexture(const char* file_name);

	//Text
	void drawText(const char* text, int x = 0, int y = 0) {tm.drawText(text, mainFont, x, y);};

	//Effects
	void shadeScreen();
	
	//GET methods
	int width() const {return screen_width;}
	int height() const {return screen_height;}
private:
	gTextManager tm;

	gFont mainFont;
	SDL_Window* mainWnd;
	SDL_Surface* screenSurface;
	SDL_Renderer* mainRend;

	SDL_Color backgroundColor;

	int screen_width;
	int screen_height;
	bool is_full_screen;

	SDL_Window* createGameWindow(const int width, const int height, bool is_full_screen = false);
	SDL_Renderer* createGameRenderer();

	static gGraphicManager* device;//Contains last successfuly initialized device
};

#endif