/*	This file is part of GEngine.
*
*Decription:
*
*Author: George Popov
*Date:
*Current Phase: In development
*/
#ifndef GFONT_H
#define GFONT_H

#include "gErrors.h"
#include <fstream>
#include <string>

using namespace std;

class gFont
{
	static const string dir;

public:
	static const string getDirectory() {return dir;};

	gFont(void);
	gFont(const char* name);
	~gFont(void);

	void readFont(const char* name);

	//GET methods
	float getSize() const {return font_size;};
	int getTileSize() const {return tile_size;};
	float getFontInterval() const {return font_interval;};
	const char* getName() const {return font_name;};

	//BOOL methods
	bool isOpen() const {return isFontReaded;};

private:
	bool isFontReaded;

	char* font_name;
	int tile_size;
	float font_interval;
	float font_size;
};

#endif