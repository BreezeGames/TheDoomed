/*	This file is part of GEngine.
*
*Decription:
*
*Author: George Popov
*Date:
*Current Phase:
*/
#ifndef GSOUND_H
#define GSOUND_H

class gSound
{
public:
	gSound(void);
	gSound(const char* file);
	~gSound(void);

	void play();
	void pause();
	void stop();
};

#endif