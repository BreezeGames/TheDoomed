/******************************************************
*
*	GEngine - 2D game engine.
* GEngine is a beautiful and simply game engine
* developed by George Popoff.
*
* George Popoff 2015.
* GEngine all rights are reserved (c).
*
*
* For more details about this product read README file.
*******************************************************/

#include <SDL.h>
#include <cstdlib>
#include "gPlayer.h"
#include "gGame.h"

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