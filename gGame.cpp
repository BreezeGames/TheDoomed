#include "gGame.h"


gGame::gGame(const int width, const int height):
	screen_height(height), screen_width(width), dir("res/")
{
	debug_mode = false;
	state = GAME_LOGIN;

	string path = dir+"loginMenu_background.bmp";
	loginMenu_background = gm.loadTexture(path.c_str());

	path = dir+"menu_background.bmp";
	menu_background = gm.loadTexture(path.c_str());

	path = dir+"menu_foreground.bmp";
	menu_foreground = gm.loadTexture(path.c_str());
}


gGame::~gGame(void)
{
	SDL_DestroyTexture(loginMenu_background);
	SDL_DestroyTexture(menu_background);
	SDL_DestroyTexture(menu_foreground);

	SDL_Quit();
}

void gGame::gDebug()
{

}

//Main mechanics update function
//All game states handles here
void gGame::updateGameState()
{
	cout << "-> Game state: " << state << endl;
	if(debug_mode)
		gDebug();

	switch(state)
	{
	case GAME_LOGIN:
		gLoginMenu();
		break;
	case GAME_MENU:
		gMenu();
		break;
	case GAME_ON:
		//LOADING MAP
		player.draw();
		break;
	case GAME_PAUSE:
		player.draw();
		break;
	case GAME_EXIT:
		SDL_Quit();
		break;
	}
}

//Draws character creation/choose menu
//Gets current character
void gGame::gMenu()
{
	if(menu_background == NULL)
	{
		string path = dir+"menu_background.bmp";
		gm.loadTexture(path.c_str());
	}
	if(menu_foreground == NULL)
	{
		string path = dir+"menu_foreground.bmp";
		gm.loadTexture(path.c_str());
	}

	gm.RenderTexture(menu_background);
	gm.RenderTexture(menu_foreground,gm.width()-30*10,gm.height()-60*10, 10);
}

void gGame::gLoginMenu()
{
	if(loginMenu_background == NULL)
	{
		string path = dir+"loginMenu_background.bmp";
		gm.loadTexture(path.c_str());
	}

	gm.RenderTexture(loginMenu_background);
	gm.drawText("Forgotted (C) 2015 all rights are reserved. Gengine - 2014-2015. All marks are reserved! You may not distribute this product without author accept!!"
		,100,500);
}

//Get key events
//Only state condition can be changed
void gGame::updateKeyEvent()
{
	if(SDL_PollEvent(&ev))
	{
		switch(ev.type)
		{
		case SDL_QUIT:
			state = GAME_EXIT;
			break;
		case SDL_KEYDOWN:
			if(state==GAME_LOGIN && ev.key.keysym.sym != SDLK_F11)
				state = GAME_MENU;

			switch (ev.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				if(state == GAME_MENU)
					state = GAME_EXIT;
				else if (state == GAME_ON)
					state = GAME_MENU;
				else if (state == GAME_PAUSE)
					state = GAME_ON;
				break;
			case SDLK_F11:
				gm.setWindowFullScreen();
				break;
			case SDLK_F12:
				debug_mode = true;
				break;
			}
		}
	}

	const Uint8 *keyState = SDL_GetKeyboardState(NULL);

	if(keyState[SDL_SCANCODE_F10])
	{
		gm.setWindowFullScreen();
	}
	if(keyState[SDL_SCANCODE_N])
	{
		if(state == GAME_MENU)
			state = GAME_ON;
	}

	if(keyState[SDL_SCANCODE_P])
	{
		if(state == GAME_ON)
			state = GAME_PAUSE;
	}

	if(keyState[SDL_SCANCODE_UP])
	{
		if(state == GAME_ON)
			player.moveY(-1);
	}

	if(keyState[SDL_SCANCODE_DOWN])
	{
		if(state == GAME_ON)
			player.moveY(1);
	}

	if(keyState[SDL_SCANCODE_LEFT])
	{
		if(state == GAME_ON)
			player.moveX(-1);
	}

	if(keyState[SDL_SCANCODE_RIGHT])
	{
		if(state == GAME_ON)
			player.moveX(1);
	}

}
//Updates all system. 
//All class mechanics 
void gGame::update()
{
	updateKeyEvent();
	updateGameState();
	gm.UpdateScreen();

	SDL_Delay(50);
}