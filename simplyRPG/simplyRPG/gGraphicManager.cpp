#include "gGraphicManager.h"

gGraphicManager* gGraphicManager::device = NULL;

gGraphicManager::gGraphicManager(const int width, const int height):screen_width(width), screen_height(height), is_full_screen(false)
{
	//INITIALIZING SDL
	if(SDL_Init(SDL_INIT_EVERYTHING))
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "Cant init SDL . . .");
	}

	//WINDOW creating
	mainWnd = createGameWindow(screen_width, screen_height);
	if(!mainWnd)
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Cant init main window . . .");

	//RENDER creating
	mainRend = createGameRenderer();
	if(!mainRend)
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Cant create main renderer . . .");

	device = this;
	screenSurface = NULL;

	//Text Manager init
	tm.init();

	//Background color
	backgroundColor.r = 150;
	backgroundColor.g = 150;
	backgroundColor.b = 200;
	backgroundColor.a = 0.7;
	SDL_SetRenderDrawColor(mainRend, backgroundColor.r,backgroundColor.g, 
		backgroundColor.b, backgroundColor.a);
}

gGraphicManager::~gGraphicManager(void)
{
	SDL_DestroyWindow(mainWnd);
	SDL_DestroyRenderer(mainRend);
	SDL_FreeSurface(screenSurface);
}

//Creates game window
//Width, height - size of the window
//Is full screen set to FALSE by default
SDL_Window* gGraphicManager::createGameWindow(const int width, const int height, bool is_full_screen)
{
	SDL_Window* wnd;

	if(!is_full_screen)
		wnd = SDL_CreateWindow("My RPG game", 200, 200, width, height, SDL_WINDOW_SHOWN);
	else
		wnd = SDL_CreateWindow("My RPG game", 0, 0, width, height, SDL_WINDOW_FULLSCREEN_DESKTOP);

	return wnd;
}

//Creates renderer and return renderer pointer
SDL_Renderer* gGraphicManager::createGameRenderer()
{
	return SDL_CreateRenderer(mainWnd, -1, SDL_RENDERER_ACCELERATED 
										 | SDL_RENDERER_PRESENTVSYNC);
}

//Try to receive graphicManager adress
gGraphicManager& gGraphicManager::getGraphicManager()
{
	if(device)
		return *device;
	else
		throw;
}

/************************************************
* Main update function. Updates screen
*
* Param td - delay in ms.
***************************************************/
void gGraphicManager::UpdateScreen(const float td)
{
	SDL_RenderPresent(mainRend);
	SDL_RenderClear(mainRend);
}

//Draws whole texture at the x,y coordinates
bool gGraphicManager::RenderTexture(SDL_Texture* texture, int x, int y, float scale, Uint8 flags)
{
	 if(!texture)
		 SDL_LogWarn(SDL_LOG_CATEGORY_RENDER, "Input texture is NULL!");

	 SDL_Rect destination;
	 destination.x = x;
	 destination.y = y;

	 SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h);

	 destination.w*=(int)scale;
	 destination.h*=(int)scale;

	 if(SDL_RenderCopy(mainRend, texture, NULL , &destination) == -1)
	 {
		 SDL_LogWarn(SDL_LOG_CATEGORY_RENDER, SDL_GetError());
		 return false;
	 }

	 return true;
}

//Draws source rectangle of texture at x,y coordinates
bool gGraphicManager::RenderTexture(SDL_Texture* texture, SDL_Rect source, int x, int y, float scale)
{
	 if(!texture)
		 SDL_LogWarn(SDL_LOG_CATEGORY_RENDER, "Input texture is NULL!");

	 SDL_Rect destination;
	 destination.x = x;
	 destination.y = y;
	 destination.w = source.w;
	 destination.h = source.h;
	// SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h);

	 destination.w*=(int)scale;
	 destination.h*=(int)scale;

	 //Apply flags changes
	 //TODO:THERE ARE FLAGS 

	 if(SDL_RenderCopy(mainRend, texture, &source , &destination) == -1)
		 return false;

	 return true;
}

//Render whole texture on the whole screen
bool gGraphicManager::RenderTexture(SDL_Texture* texture, Uint8 flags)
{
	 if(!texture)
		 SDL_LogWarn(SDL_LOG_CATEGORY_RENDER, "Input texture is NULL!");

	 SDL_Rect destination;
	 destination.x = 0;
	 destination.y = 0;
	 destination.w = screen_width;
	 destination.h = screen_height;

	 //Apply flags changes
	 if(flags == 1)
		 SDL_SetTextureColorMod(texture, 180, 50, 50);

	 if(SDL_RenderCopy(mainRend, texture, NULL , &destination) == -1)
	 {
		 SDL_LogWarn(SDL_LOG_CATEGORY_RENDER, SDL_GetError());
		 return false;
	 }

	 return true;
}

//Loads texture from the file.
//@arg file_name - name of the file to load.
//WARNING: only BMP files attempt.
//If it is no such file in the directory - used default image.
SDL_Texture* gGraphicManager::loadTexture(const char* file_name)
{
	screenSurface = SDL_LoadBMP(file_name);

	if(!screenSurface)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_RENDER, "Can't load texture: %s", file_name);
		//USE DEFAULT IMAGE FOR THAT CASE
	}

	SDL_SetColorKey(screenSurface, 1, SDL_MapRGB(screenSurface->format, 255,0,255));
	SDL_Texture* texture = SDL_CreateTextureFromSurface(mainRend, screenSurface);
	SDL_FreeSurface(screenSurface);

	return texture;
}

//Set window to the full screen mode
void gGraphicManager::setWindowFullScreen()
{
	if(is_full_screen)
		return;
	else
	{
		SDL_SetWindowFullscreen(mainWnd, SDL_WINDOW_FULLSCREEN_DESKTOP);
		SDL_SetWindowDisplayMode(mainWnd, NULL);
		SDL_GetWindowSize(mainWnd, &screen_width, &screen_height);
	}
	is_full_screen = true;
}

//Get texture width and height
SDL_Point gGraphicManager::getTextureSize(SDL_Texture* texture) 
{
	SDL_Point size;
	SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);

	return size;
}

//Sets render draw color
//@arg color - desired color.
void gGraphicManager::setRenderDrawColor(SDL_Color color)
{
	SDL_SetRenderDrawColor(mainRend, color.r, color.g, color.b, color.a);
}

void gGraphicManager::setRenderDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(mainRend, r, g, b, a);
}

//Shades the screen
void gGraphicManager::shadeScreen()
{
	//Left and right blocks(Grey) // Main Color to shade screen.(black)
	SDL_Color add_shade_color;  SDL_Color shade_color;
	add_shade_color.r = 100;		shade_color.r = 50;
	add_shade_color.g = 100;		shade_color.g = 50;
	add_shade_color.b = 100;		shade_color.b = 50;
	add_shade_color.a = 200;		shade_color.a = 200;

	setRenderDrawColor(shade_color);
	SDL_SetRenderDrawBlendMode(mainRend, SDL_BLENDMODE_BLEND);

	//Middle part of the shader
	SDL_Rect screen;
	screen.x = width()*0.2;
	screen.y = 0;
	screen.w = width() - width()*0.4;
	screen.h = screen_height;
	SDL_RenderFillRect(mainRend, &screen);

	setRenderDrawColor(add_shade_color);
	//Left part
	screen.x = 0;
	screen.w = width()*0.2;
	SDL_RenderFillRect(mainRend, &screen);

	//Right part
	screen.x = width() - width()*0.2;
	screen.w = width()*0.2;
	SDL_RenderFillRect(mainRend, &screen);

	setRenderDrawColor(backgroundColor);
	SDL_SetRenderDrawBlendMode(mainRend, SDL_BLENDMODE_NONE);
}

