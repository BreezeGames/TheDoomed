#include "gTextManager.h"
#include <fstream>
#include <iostream>
#include <string>
#include "gGraphicManager.h"

map<char, int> gTextManager::char_map;

gTextManager::gTextManager(void)
{
	loadCharMap();
}

void gTextManager::init()
{
	gGraphicManager &gm = gGraphicManager::getGraphicManager();
	map_texture = gm.loadTexture("res/chars.bmp");
}

gTextManager::~gTextManager(void)
{
}

void gTextManager::loadCharMap()
{
	cout << "gTextManager: loading characters map . . ." << endl;
	string path = gFont::getFontsDirectory();
	path+="map.gcm";

	ifstream font(path);

	char_map[' '] = 0;

	int count = 1;
	char ch = ' ';
	while(font)
	{
		font >> ch;
		char_map[ch] = count++; 
		cout << ch << ":" << char_map[ch] << "\t";
		if(count == 10)
			cout << endl;
	}


}

void gTextManager::drawText(const char* string, gFont font, int x, int y)
{
	gGraphicManager &gm = gGraphicManager::getGraphicManager();
	int symbol_numb = 0;
	int posX, posY;
	SDL_Rect source;

	float font_interval = font.getFontInterval();
	int tile_size = font.getTileSize();
	float size = font.getSize();
	
	while (*string)
	{
		cout << "->gTextManager: drawing " << char_map[*string] << ":" << *string << " symbol!" << endl;



		posX = char_map[*string];
		posY = char_map[*string] / 9;
		posX -= posY * 9;

		source.x = posX*tile_size;
		source.y = posY*tile_size;
		source.w = tile_size;
		source.h = tile_size;

		/*std::string msg;
		stringstream ss;

		gm.drawText(string, 0,0);*/

		if ((x + (symbol_numb*font_interval*size*tile_size)) > gm.width() - 100 ||
			(x + (symbol_numb*font_interval*size)) < 0 + 100)
		{
			symbol_numb = 0;
			y += ((font_interval+0.2)*tile_size*size);//WARNING maybe y must be float...
		}

		gm.RenderTexture(map_texture, source, x + symbol_numb*(font_interval*tile_size*size), y, size);

		*string++;
		symbol_numb++;
	}
}