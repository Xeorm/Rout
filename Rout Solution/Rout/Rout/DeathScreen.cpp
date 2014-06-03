#include "DeathScreen.h"
#include "StateManager.h"
#include "GameMenu.h"
#include <sstream>
#include "Main.h"
DeathScreen* DeathScreen::ds_instance=NULL;
DeathScreen* DeathScreen::getInstance()
{
	if(ds_instance == NULL)
	{
		ds_instance = new DeathScreen();
	}
	
	return ds_instance;
}

DeathScreen::DeathScreen()
{
	const int left = 335;
	textFields.push_back(TextField(left,200,"Restart"));
	textFields.push_back(TextField(left,250,"Main Menu"));
	textFields.push_back(TextField(left,300,"Exit"));
	list<TextField>::iterator it;
	//enumerate through text field array
	for ( it=textFields.begin() ; it != textFields.end(); it++ )
	{
		//check if inside text field area
		EntityManager::getInstance()->textFieldList.push_back(&(*it));
	}
	EntityManager::getInstance()->textFieldList.push_back(new TextField(left+30,150,"You Died!"));
}

void DeathScreen::handleLeftDownClick(int x,int y)
{

		
	list<TextField>::iterator it;
	//enumerate through text field array
	for ( it=textFields.begin() ; it != textFields.end(); it++ )
	{
		//check if inside text field area
		if (x > it->loc.left && y > it->loc.top && x < it->loc.right && y < it->loc.bottom)
		{
			it->mouseDown();
		}
	}
}

void DeathScreen::handleMouseMoving(int x,int y)
{
	list<TextField>::iterator it;

	//enumerate through text field array
	for ( it=textFields.begin() ; it != textFields.end(); it++ )
	{
		it->mouseOver(false);
		//check if inside text field area
		if (x > it->loc.left && y > it->loc.top && x < it->loc.right && y < it->loc.bottom)
		{
			it->mouseOver(true);
		}
		
	}
}
int DeathScreen::handleLeftUpClick(int x,int y)
{
	list<TextField>::iterator it;

	//enumerate through text field array
	for ( it=textFields.begin() ; it != textFields.end(); it++ )
	{	
		it->mouseUp();
		//check if inside text field area
		if (x > it->loc.left && y > it->loc.top && x < it->loc.right && y < it->loc.bottom)
		{
			return handleButton(it->getText());
		}
	}
	return 0;
}

DeathScreen::~DeathScreen()
{
	ds_instance = NULL;
}
int DeathScreen::handleButton(string value)
{
	//do stuff based on which button is clicked
	if (value.compare("Restart")==0)
	{
		StateManager::getInstance()->changeState(InGame);
		ds_instance->~DeathScreen();
		return 2;
	}
	if (value.compare("Main Menu")==0)
	{
		ds_instance->~DeathScreen();
			return 3;
		
	}
	if (value.compare("Exit")==0)
	{
		return 1;
	}
	return 0;
}
