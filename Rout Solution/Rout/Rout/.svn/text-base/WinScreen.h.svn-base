#pragma once
#include <string>
#include <list>
#include "MenuButton.h"
#include "TextField.h"
/* Alex Jones: Death screen to display when the player dies
*/
class WinScreen
{
public:
	static WinScreen* getInstance();
	~WinScreen(void);
	void handleLeftDownClick(int,int);
	int handleLeftUpClick(int,int);
	void handleMouseMoving(int,int);

private:
	static WinScreen* ws_instance;
	list<TextField> textFields;
	WinScreen();
	int handleButton(string);
};