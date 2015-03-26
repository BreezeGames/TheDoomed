#include <iostream>
#include "gFont.h"

//TODO: maybe not use global string
const string gFont::dir = "fonts/";

gFont::gFont(void):isFontReaded(false), font_size(0.4f),
	font_name("default"), tile_size(8), font_interval(2.0f)
{
	try
	{
		string path = dir + "default.gf";
		readFont("fonts/default.gf");
	}
	catch(err::ERROR_CRITICAL err)
	{
		cerr << err.msg << endl;
		return;
	}
}

gFont::gFont(const char* name):isFontReaded(false), font_size(0.4f),
	font_name("default"), tile_size(8)
{
	try
	{
		string path = dir + name;
		readFont(path.c_str());
	}
	catch(err::ERROR_CRITICAL err)
	{
		cerr << err.msg << endl;
		return;
	}
}

//Reads font from the file
//File must be placed in the fonts/ directory
//gf - mainFont format
void gFont::readFont(const char* name)
{
	ifstream font(name);

	//If there no such file in the directory
	if(!font)
		throw(err::ERROR_CRITICAL("gTextManager: No such font in the directory!"));

	string n;
	font >> n;
	font_name = const_cast<char*> (n.c_str());

	float i = 0.0f;

	font >> i;
	tile_size = (int)i;

	font >> i;
	font_size = i;

	font >> i;
	font_interval = i;
	
	isFontReaded = true;
	font.close();
}

gFont::~gFont(void)
{
}
