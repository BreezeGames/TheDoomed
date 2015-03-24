#pragma once

class gSound
{
public:
	gSound(void);
	gSound(const char* file);
	~gSound(void);

	void play();
	void pause();
	void stop();

private:

};

