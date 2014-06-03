#include "WinScreen.h"
#include "StateManager.h"
#include "GameMenu.h"
#include <sstream>
#include "Main.h"
WinScreen* WinScreen::ws_instance=NULL;
WinScreen* WinScreen::getInstance()
{
	if(ws_instance == NULL)
	{
		ws_instance = new WinScreen();
	}
	
	return ws_instance;
}

WinScreen::WinScreen()
{
	const int left = 510;
	textFields.push_back(TextField(left,350,"Play Again"));
	textFields.push_back(TextField(left,400,"Main Menu"));
	textFields.push_back(TextField(left,450,"Exit"));
	list<TextField>::iterator it;
	//enumerate through text field array
	for ( it=textFields.begin() ; it != textFields.end(); it++ )
	{
		//check if inside text field area
		EntityManager::getInstance()->textFieldList.push_back(&(*it));
	}
	EntityManager::getInstance()->textFieldList.push_back(new TextField(left-300,350,"You Escaped!"));
}

void WinScreen::handleLeftDownClick(int x,int y)
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

void WinScreen::handleMouseMoving(int x,int y)
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
int WinScreen::handleLeftUpClick(int x,int y)
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

WinScreen::~WinScreen()
{
	ws_instance = NULL;
}
int WinScreen::handleButton(string value)
{
	//do stuff based on which button is clicked
	if (value.compare("Play Again")==0)
	{
		StateManager::getInstance()->changeState(InGame);
		ws_instance->~WinScreen();
		return 2;
	}
	if (value.compare("Main Menu")==0)
	{
		ws_instance->~WinScreen();
			return 3;
		
	}
	if (value.compare("Exit")==0)
	{
		return 1;
	}
	return 0;
}