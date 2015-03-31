/*	This file is part of GEngine.
*
*Decription:
*
*  Widget class: buttons, slides, textfields
*Author: George Popov
*Date: 28.03.2015
*Current Phase: Projecting
*/

#ifndef IWIDGET_H
#define IWIDGET_H

#include "IDrawble.h"

class IWidget :
	public IDrawble
{
public:
	//CONSTRUCTORS
	IWidget(const int id, const char* texture);
	IWidget(const IWidget&);

	//INTERFACE methods
	void draw();
	void remove();
	bool load();

	//EVENT methods
	void onClick();
	void onFocused();
private:
};
#endif

