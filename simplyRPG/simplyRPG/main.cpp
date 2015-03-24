#include <SDL.h>
#include <cstdlib>
#include "gPlayer.h"
#include "gGame.h"

//gGame engine - v 0.0001a
//DEVELOPED by George Popov - 2014 (c)
int main(int argc, char* argv[])
{	
	//CREATE MAIN GAME CLASS
	gGame game(800, 600);

	//MAIN CIRCLE
	while(true)
	{	
		game.update();
	}

	return 0;
}