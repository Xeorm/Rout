#pragma once
#include <iostream>
#include <string>
#include "GameEntity2D.h"
using namespace std;

//Enums for button types...add for a new button
enum ButtonName {Exit = 0};

class MenuButton:public GameEntity2D
{
protected:
	int mb_x;
	int mb_y;
	ButtonName name;
	int mb_width;
	int mb_length;
	string mb_graphicPath;

public:
	MenuButton(LPCSTR tex);
	MenuButton(void);
	MenuButton(int x, int y,string);
	~MenuButton(void);
	virtual void interact(void);
	int X(void) const;
	int Y(void) const;
	int Length(void) const;
	int Width(void) const;
	ButtonName Name(void) const;
};

