#include "gPlayer.h"

//Default constructor
gPlayer::gPlayer(void) : name("adventurer"), dir("players/"), speed(5.5f)
{
	gGraphicManager &gm = gGraphicManager::getGraphicManager();

	//PLAYER loading
	load();

	//TEXTURE loading
	default_texture = gm.loadTexture(string(dir+"default.bmp").c_str());
}


gPlayer::gPlayer(string player_name) : name(player_name)
{
	createNewPlayer();
}

gPlayer::gPlayer(int player_id)
{
	id = player_id;
	load();
}

//Loading IDrawble object
bool gPlayer::load()
{
	gGraphicManager &gm = gGraphicManager::getGraphicManager();

	//Player loading
	texture = gm.loadTexture(string(dir + "player.bmp").c_str());

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
	if (texture)
		gm.RenderTexture(texture, coords.x, coords.y, 5);
	else
		gm.RenderTexture(default_texture, coords.x, coords.y, 5);

	//Draw position 
	gm.drawText(name.c_str(), coords.x, coords.y - 15 / 2);
}


//Remove player from the screen
void gPlayer::remove()
{
	//Remove
}
