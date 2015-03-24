#ifndef GAME
#define GAME

#include <SDL.h>
#include <string>
#include <iostream>
#include <list>
#include "gFont.h"
#include "gGraphicManager.h"
#include "gPlayer.h"
#include "gErrors.h"

using namespace std; 

enum gGameState{ GAME_MENU = 1, GAME_LOGIN = 2, GAME_PAUSE = 3,
				 GAME_ON = 4, GAME_EXIT = 0};
class gGame
{
public:
	gGame(int width, int height);
	
	//UPDATE functions
	void updateGameState();//Update current game state.
	void update();//Updates all classes mechanics
	void updateKeyEvent();

	int getCurrentPlayerID();

	gGameState getGameState() const {return state;}//Returns current game state

	//Returns list of current players
	list<string> getExistsPlayers() const;

	//DRAW functions
	void gLoginMenu();
	void gMenu();
	void gDebug();

	gGraphicManager* getGraphicDevice() {return &gm;};//Allows different classes use this method
	~gGame(void);
private:
	bool debug_mode;
	gGraphicManager gm;//Draw functions and texture loading
	gGameState state;
	gPlayer player;

	int screen_width;
	int screen_height;

	SDL_Texture* loginMenu_background;
	SDL_Texture* menu_foreground;
	SDL_Texture* menu_background;

	SDL_Event ev;
	const string dir;
};

#endif