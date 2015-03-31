/*	This file is part of GEngine.
*
*Decription:
*
*Author: George Popov
*Date:
*Current Phase: 
*/
#ifndef GPLAYER
#define GPLAYER

#include "idrawble.h"
#include <string>

using namespace std;
class gPlayer : public IDrawble
{
public:
	gPlayer(void);
	gPlayer(string name);
	gPlayer(int player_id);

	~gPlayer(void);

	//INTERFACE methods
	void draw();
	void remove();
	bool load();

	void moveX(int dx) {coords.x += (int)speed*dx;}
	void moveY(int dy) {coords.y += (int)speed*dy;}
	
	bool createNewPlayer();
private:
	float speed;

	string name;
	const string dir; //Player recources dir
	SDL_Texture* texture; //Main player texture
};

#endif
