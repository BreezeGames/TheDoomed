#include <fstream>
#include <iostream>
#include <string>
#include "gGraphicManager.h"

using namespace gtext;

map<char, int> gTextManager::char_map;

gTextLayout::gTextLayout(const char* plain_text, SDL_Rect reg, gFont f, int sz, G_TEXT_ALIGN text_align,
	float lPadding,float rPadding) :
	text(plain_text), region(reg), leftPadding(lPadding), rightPadding(rPadding), size(sz)
{
	align = text_align;

	font = f;
	//Set up the layout
	gTextManager::setTextLayout(*this);
}

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

void gTextManager::setTextLayout(gTextLayout& layout)
{
	layout.realRegion.x = layout.region.x + (int)(layout.region.w*layout.leftPadding);
	layout.realRegion.y = layout.region.y + (int)(layout.region.h*0.05);//Top padding is constant (5)

	layout.realRegion.w = layout.region.w - layout.realRegion.x - (int)(layout.region.w*layout.rightPadding);
	layout.realRegion.h = layout.region.h - layout.realRegion.y - (int)(layout.region.h*0.05);//Top padding is constant (5)
}

int gTextManager::getTextWidth(const char* text, gFont font, int scale)
{
	int length = 0;
	int width = 0;

	while (*text)
	{
		length++;
		*text++;
	}
	

	width = length * font.getTileSize() * scale;//Letters width
	width += (int)(font.getFontInterval() * font.getTileSize() * (length - 1) * scale);//Spacing width

	return width;
}

int gTextManager::getTextWidth(gTextLayout l)
{
	int length = 0;
	int width = 0;

	while (*l.text && *l.text != '\n')
	{
		length++;
		*l.text++;
	}

	width = length * l.font.getTileSize() * l.size;//Letters width
	width += (length-1) * l.font.getFontInterval() * l.size;
	return width;
}
void gTextManager::drawText(const char* string, gFont font, int x,
			int y, int font_size)
{
	gGraphicManager &gm = gGraphicManager::getGraphicManager();

	int symbol_numb = 0;
	int posX, posY;
	SDL_Rect source;

	float font_interval = font.getFontInterval();
	float size = font.getSize()*font_size;
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
			y += (int)((font_interval + 0.2)*tile_size*size);
		}

		gm.RenderTexture(map_texture, source, x + (int)(symbol_numb*(font_interval*tile_size*size)), y, size);

		symbol_numb++;
		*string++;
	}
}

void gTextManager::drawText(gTextLayout text)
{
	gGraphicManager &gm = gGraphicManager::getGraphicManager();

	int posX, posY;

	float font_interval = text.font.getFontInterval();
	float size = text.font.getSize()*text.size;
	int tile_size = text.font.getTileSize();

	SDL_Rect source; //For spritesheet

	int i_x = 0; //Initial x
	int x = 0;
	int y = 0;

#ifdef DEBUG
	SDL_Color red;
	red.r = 255; red.g = 0; red.b = 0; red.a = 0;

	gm.drawLine(gm.width() / 2, 0, gm.width() / 2, gm.height(), &red);
#endif

	if (text.align == 0)
	{
		i_x = text.region.w / 2 - (getTextWidth(text) / (text.size+1));
		y = text.region.h / 2;
	}
	else if (text.align == 1)
	{
		i_x = text.realRegion.x; 
		y = text.realRegion.y; 
	}
	else if (text.align == 2)
	{
		i_x = text.realRegion.x - getTextWidth(text);
		y = text.realRegion.y;
	}

	while (*text.text)
	{
		posX = char_map[*text.text];
		posY = char_map[*text.text] / 9;
		posX -= posY * 9;

		source.x = posX*tile_size;
		source.y = posY*tile_size;
		source.w = tile_size;
		source.h = tile_size;

		x += (int)(font_interval*tile_size*size);

		if ((*text.text == '\n'))
		{
			x = i_x;
			y += (int)((font_interval + 0.2)*tile_size*size);
		}
		else if (x > text.realRegion.w	||
			    (x < text.realRegion.x))
		{
			x = i_x;
			y += (int)((font_interval + 0.2)*tile_size*size);
		}
		//If the next symbol is 'space' there is a small bug
		if (!(x == i_x && *text.text == ' '))
			gm.RenderTexture(map_texture, source, x, y, size);
		else
			x -= (int)(font_interval*tile_size*size);

		*text.text++;
	}	
}