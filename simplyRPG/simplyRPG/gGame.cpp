#include "gGame.h"


gGame::gGame(const int width, const int height): dir("res/")
{
	state = GAME_LOGIN;//INITIAL STATE

	//Textures loading
	string path = dir+"loginMenu_background.bmp";
	loginMenu_background = gm.loadTexture(path.c_str());

	path = dir+"menu_background.bmp";
	menu_background = gm.loadTexture(path.c_str());

	path = dir+"menu_foreground.bmp";
	menu_foreground = gm.loadTexture(path.c_str());
	//End of textures loading

	//Init font
}


gGame::~gGame(void)
{
	//Textures destroying
	SDL_DestroyTexture(loginMenu_background);
	SDL_DestroyTexture(menu_background);
	SDL_DestroyTexture(menu_foreground);
	//End of textures destroying
	SDL_Quit();
}

//TODO
void gGame::gDebug()
{
}

//Main mechanics update function
//All game states handles here
void gGame::updateGameState()
{
	switch(state)
	{
	case GAME_LOGIN:
		gLoginMenu();
		break;
	case GAME_MENU:
		gMenu();
		break;
	case GAME_ON:
		player.draw();
		break;
	case GAME_PAUSE:
		player.draw();
		gGamePaused();
		break;
	case GAME_EXIT:
		SDL_Quit();
		exit(0);
		break;
	}
}

//Draws character creation/selecting menu
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

//Start screent. 
//LoginMenu in project supposed to be a login in form.
void gGame::gLoginMenu()
{
	if(loginMenu_background == NULL)
	{
		string path = dir+"loginMenu_background.bmp";
		gm.loadTexture(path.c_str());
	}

	gm.RenderTexture(loginMenu_background);
	gm.drawText("Forgotted (C) 2015 all rights are reserved. Gengine - 2014-2015. All marks are reserved! "
		"You may not distribute this product without author accept!!", 100, gm.height() - 50);
}

//Get key events
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

			//Switching pressed key
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
			}
			//End of switching
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

	SDL_Delay(50);//Game fps
}

//Draws pause screen
void gGame::gGamePaused()
{
	SDL_Rect region;
	region.x = 0;
	region.y = 0;
	region.w = gm.width();
	region.h = gm.height();

	gm.shadeScreen();

	gtext::gTextLayout textLayout("On the other hand, we denounce with righteous indignation and dislike men who are so beguiled and demoralized by the charms of pleasure of the moment, so blinded by desire, that they cannot foresee the pain and trouble that are bound to ensue; and equal blame belongs to those who fail in their duty through weakness of will, which is the same as saying through shrinking from toil and pain.These cases are perfectly simple and easy to distinguish.In a free hour, when our power of choice is untrammelled and when nothing prevents our being able to do what we like best, every pleasure is to be welcomed and every pain avoided.But in certain circumstances and owing to the claims of duty or the obligations of business it will frequently occur that pleasures have to be repudiated and annoyances accepted.The wise man therefore always holds in these matters to this principle of selection : he rejects pleasures to secure other greater pleasures, or else he endures pains to avoid worse pains.",
		region, default_font, 1, gtext::G_TEXT_ALIGN_LEFT);
	
	gm.renderTextLayout(textLayout);
}