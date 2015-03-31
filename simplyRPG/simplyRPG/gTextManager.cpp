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
	SDL_DestroyTexture(map_texture);
}

void gTextManager::loadCharMap()
{
	string path = gFont::getDirectory();
	path += "map.gcm";

	ifstream font(path);

	char_map[' '] = 0;

	int count = 1;
	char ch = ' ';

	while(font)
	{
		font >> ch;
		char_map[ch] = count++; 
	}
}

void gTextManager::drawText(const char* string, gFont font, int x, int y)
{
	gGraphicManager &gm = gGraphicManager::getGraphicManager();

	int symbol_numb = 0;
	int posX, posY;
	SDL_Rect source;

	float font_interval = font.getFontInterval();
	float size = font.getSize();
	int tile_size = font.getTileSize();
	
	while (*string)
	{
		posX = char_map[*string];
		posY = char_map[*string] / 9;
		posX -= posY * 9;

		source.x = posX*tile_size;
		source.y = posY*tile_size;
		source.w = tile_size;
		source.h = tile_size;


		if ((x + (symbol_numb*font_interval*size*tile_size)) > gm.width() - 100 ||
			(x + (symbol_numb*font_interval*size)) < 0 + 100)
		{
			symbol_numb = 0;
			y += (int)((font_interval+0.2)*tile_size*size);
		}

		gm.RenderTexture(map_texture, source, x + (int)(symbol_numb*(font_interval*tile_size*size)), y, size);

		symbol_numb++;
		*string++;
	}
}