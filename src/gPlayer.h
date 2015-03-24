#ifndef GPLAYER
#define GPLAYER

#include "idrawble.h"
#include <string>

using namespace std;
class gPlayer : public IDrawble
{
public:
	gPlayer(void);
	gPlayer(string name);
	gPlayer(int player_id);

	~gPlayer(void);

	void draw();
	void remove();
	void moveX(int dx) {x += speed*dx;}
	void moveY(int dy) {y += speed*dy;}

	bool load();
	bool createNewPlayer();
private:
	float speed;

	string name;
	const string dir;
	SDL_Texture* texture; //Основная текстура персонажа.
};

#endif
