#pragma once
#include "gErrors.h"
#include <fstream>
#include <string>

using namespace std;
class gFont
{
	static const string dir;

public:
	gFont(void);
	gFont(const char* name);
	~gFont(void);

	static const string getFontsDirectory() {return dir;};
	void readFont(const char* name);

	float getSize() const {return font_size;};
	int getTileSize() const {return tile_size;};
	float getFontInterval() const {return font_interval;};
	const char* getName() const {return font_name;};

	bool isOpen() const {return isFontReaded;};

private:
	bool isFontReaded;

	char* font_name;
	int tile_size;
	float font_interval;
	float font_size;
};

