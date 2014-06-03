#pragma once
#include <string>
#include <list>
#include "MenuButton.h"
#include "TextField.h"
/* Dan Corey: Contains a list of buttons that the menu is made up of. Bool 'title' is to determine whether it's the title menu, or pause menu.
May make seperate classes if they wildly differ, but should have similar code.
*/
class GameMenu
{
public:
	static GameMenu* getInstance();
	void changeMenu(bool isTitle); //switches between title and options
	~GameMenu(void);
	void handleLeftDownClick(int,int);
	int handleLeftUpClick(int,int);
	void handleMouseMoving(int,int);
	void options();
private:
	static GameMenu* gm_instance;
	GameMenu(bool);
	bool title;
	list<TextField> textFields;
	int handleButton(string);
};

