#include "gPlayer.h"

//Default constructor
gPlayer::gPlayer(void) : name("adventurer"), dir("players/"), speed(5.5f)
{
	cout << "Game: creating character . . ." << endl;
	id = 0;
	x = 0;
	y = 0;

	gGraphicManager &gm = gGraphicManager::getGraphicManager();
	texture = gm.loadTexture(string(dir+"player.bmp").c_str());
	default_texture = gm.loadTexture(string(dir+"default.bmp").c_str());
}
//Create new player
gPlayer::gPlayer(string player_name) : name(player_name)
{
	createNewPlayer();
}

//If player has already been created
gPlayer::gPlayer(int player_id)
{
	id = player_id;
	load();
}

//Loading IDrawble object
bool gPlayer::load()
{
	//loading player

	return true;
}

//Create new player
bool gPlayer::createNewPlayer()
{
	//creating code
	return true;
}
gPlayer::~gPlayer(void)
{
	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(default_texture);
}

//Draw player on the screen
void gPlayer::draw()
{
	gGraphicManager &gm = gGraphicManager::getGraphicManager();

	//Draw player
	if(texture)
		gm.RenderTexture(texture, x, y, 5);
	else
		gm.RenderTexture(default_texture, x, y, 5);

	//Draw position 
	gm.drawText(name.c_str(), x, y - 15 / 2);
}


//Remove player from the screen
void gPlayer::remove()
{
	//Remove
}
