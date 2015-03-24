#include "gGraphicManager.h"

gGraphicManager* gGraphicManager::device = NULL;

//Creates graphicManager device. Need two arguments: size of the screen.
//!Also creates a window
gGraphicManager::gGraphicManager(const int width, const int height):screen_width(width), screen_height(height), is_full_screen(false)
{
	if(SDL_Init(SDL_INIT_EVERYTHING))
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "Cant init SDL . . .");
	}

	mainWnd = createGameWindow(screen_width, screen_height);

	if(!mainWnd)
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Cant init main window . . .");

	mainRend = createGameRenderer();

	if(!mainRend)
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Cant create main renderer . . .");

	device = this;
	screenSurface = NULL;

	tm.init();
}

//Delete all stuff
gGraphicManager::~gGraphicManager(void)
{
	SDL_DestroyWindow(mainWnd);
	SDL_FreeSurface(screenSurface);
	SDL_DestroyRenderer(mainRend);
}

//Creates game window
//Width, height - size of the window
//Is full screen set to FALSE by default
SDL_Window* gGraphicManager::createGameWindow(const int width, const int height, bool is_full_screen)
{
	cout << "SDL: creating game window . . ." << endl;
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
	cout << "SDL: creating game renderer . . ." << endl;
	SDL_Renderer* rend = SDL_CreateRenderer(mainWnd, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	return rend;
}

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

//Overloaded variant 1 of render function
//Draws whole texture on the x,y point
bool gGraphicManager::RenderTexture(SDL_Texture* texture, int x, int y, float scale, Uint8 flags)
{
	cout << "->Render texture!" << endl;
	 if(!texture)
		 SDL_LogWarn(SDL_LOG_CATEGORY_RENDER, "Input texture is NULL!");

	 SDL_Rect destination;
	 destination.x = x;
	 destination.y = y;

	 SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h);

	 destination.w*=scale;
	 destination.h*=scale;

	 if(SDL_RenderCopy(mainRend, texture, NULL , &destination) == 0)
	 {
		 SDL_LogWarn(SDL_LOG_CATEGORY_RENDER, SDL_GetError());
		 return false;
	 }

	 return true;
}

//Second variant of the render function
//Draws source rectangle of texture
bool gGraphicManager::RenderTexture(SDL_Texture* texture, SDL_Rect source, int x, int y, float scale)
{
	cout << "->Render texture!" << endl;
	 if(!texture)
		 SDL_LogWarn(SDL_LOG_CATEGORY_RENDER, "Input texture is NULL!");

	 SDL_Rect destination;
	 destination.x = x;
	 destination.y = y;
	 destination.w = source.w;
	 destination.h = source.h;
	// SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h);

	 destination.w*=scale;
	 destination.h*=scale;

	 //Apply flags changes

	 if(SDL_RenderCopy(mainRend, texture, &source , &destination) == 0)
	 {
		 return false;
	 }

	 return true;
}

//Most simply render function
//Render whole texture on the whole screen
bool gGraphicManager::RenderTexture(SDL_Texture* texture, Uint8 flags)
{
	cout << "->Render texture!" << endl;
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

	 if(SDL_RenderCopy(mainRend, texture, NULL , &destination) == 0)
	 {
		 SDL_LogWarn(SDL_LOG_CATEGORY_RENDER, SDL_GetError());
		 return false;
	 }

	 return true;
}

//Loads texture from the file. file_name - full file name.
//WARNING: only BMP files attempt.
//If no such file in the directory - used default image.
SDL_Texture* gGraphicManager::loadTexture(const char* file_name)
{
	cout << "->Loading " << file_name << " texture . . ." << endl;
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
	cout << "Screen has been setup to full screen mode! "
		 << screen_width << "x" << screen_height << endl;
	}

	is_full_screen = true;
}

void gGraphicManager::shadeScreen()
{
}