/*	This file is part of GEngine.
*
*Decription:
*
*Author: George Popov
*Date:
*Current Phase:
*/
#ifndef GTEXT_H
#define GTEXT_H

#include <SDL.h>
#include <map>
#include <string>
#include "gFont.h"
#include "gErrors.h"

using namespace std;

//TODO: FIX Fonts (they are different size)
namespace gtext
{
	//This flags should be used in gTextLayout structure
	enum G_TEXT_ALIGN {G_TEXT_ALIGN_CENTER, G_TEXT_ALIGN_LEFT, G_TEXT_ALIGN_RIGHT};

	//Text layout. 
	//Plain text with drawing region and text formating attributes
	struct gTextLayout
	{
		//@arg leftPadding, rightPadding - padding of the text in percent.
		gTextLayout(const char* text, SDL_Rect region, gFont font, int size = 1, G_TEXT_ALIGN = G_TEXT_ALIGN_LEFT, float leftPadding = 0.1f,
			float rightPadding = 0.1f);

		const char* text;			//Plain text

		gFont font;			//Text font
		int size;			//Text size;

		SDL_Rect region;	//The region in witch the text should be rendered
		SDL_Rect realRegion;//Setted up by setTextLayout function
							//This is a real coordinates of text based on padding
		SDL_Color color;	//Colour of the text

		float leftPadding;	//Left padding in percents!
		float rightPadding;	//Right padding in percents!

		G_TEXT_ALIGN align; //Text align
	};

	class gTextManager
	{
	public:
		//STATIC methods
		//Set all atributtes in layout. Allows to draw it
		static void setTextLayout(gTextLayout& layout);

		//
		//static void centerText(int current_position, )
	public:
		gTextManager(void);
		~gTextManager(void);

		void init();

		//LOAD methods
		void loadCharMap();

		//Render methods
		void drawText(const char* text, gFont font, int, int, int size = 1);
		void drawText(gTextLayout text);

		//GET methods
		//Get text width in pixels.
		int getTextWidth(const char* text, gFont font, int scale);
		int getTextWidth(gTextLayout layout);

	private:
		SDL_Texture* map_texture;
		static map<char, int> char_map;//Contains ASCII charset
	};

}
#endif