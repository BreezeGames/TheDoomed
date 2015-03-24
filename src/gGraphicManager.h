#pragma once
#include <SDL.h>
#include "gTextManager.h"
#include <iostream>

using namespace std;

class gGraphicManager
{
public:
	static gGraphicManager& getGraphicManager(); 
	gGraphicManager(const int width = 800,const int height = 600);
	~gGraphicManager(void);

	void UpdateScreen(const float dt = 0);

	bool RenderTexture(SDL_Texture* texture, Uint8 flags = 0);
	bool RenderTexture(SDL_Texture* texture, SDL_Rect source, int x = 0, int y = 0, float scale = 1.0f);
	bool RenderTexture(SDL_Texture* texture, int x, int y, float scale = 1.0f, Uint8 flags = 0);

	void setWindowFullScreen();
	SDL_Texture* loadTexture(const char* file_name);

	//Text
	void drawText(const char* text, int x = 0, int y = 0) {tm.drawText(text, mainFont, x, y);};
	//Effects
	void shadeScreen();

	int width() const {return screen_width;}
	int height() const {return screen_height;}
private:
	gTextManager tm;

	gFont mainFont;
	SDL_Window* mainWnd;
	SDL_Surface* screenSurface;
	SDL_Renderer* mainRend;

	int screen_width;
	int screen_height;
	bool is_full_screen;

	SDL_Window* createGameWindow(const int width, const int height, bool is_full_screen = false);
	SDL_Renderer* createGameRenderer();

	static gGraphicManager* device;
};

