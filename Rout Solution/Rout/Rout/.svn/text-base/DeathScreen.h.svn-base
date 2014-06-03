#pragma once
#include <string>
#include <list>
#include "MenuButton.h"
#include "TextField.h"
/* Alex Jones: Death screen to display when the player dies
*/
class DeathScreen
{
public:
	static DeathScreen* getInstance();
	~DeathScreen(void);
	void handleLeftDownClick(int,int);
	int handleLeftUpClick(int,int);
	void handleMouseMoving(int,int);

private:
	static DeathScreen* ds_instance;
	list<TextField> textFields;
	DeathScreen();
	int handleButton(string);
};