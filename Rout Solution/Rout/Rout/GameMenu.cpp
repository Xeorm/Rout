#include "GameMenu.h"
#include "StateManager.h"
#include <sstream>
#include "Main.h"
GameMenu* GameMenu::gm_instance=NULL;
GameMenu* GameMenu::getInstance()
{
	if(gm_instance == NULL)
	{
		gm_instance = new GameMenu(true); //default
	}
	
	return gm_instance;
}
void GameMenu::changeMenu(bool isTitle)
{

		gm_instance->~GameMenu();
		gm_instance= new GameMenu(isTitle);
}

void GameMenu::options()
{
	gm_instance->~GameMenu();
	gm_instance = new GameMenu(false);
}

GameMenu::GameMenu(bool isTitle)
{
	title = isTitle;
	const int left = 335;
	if (title)
	{
		//make buttons for the title screen and add them to the vector array
		
		textFields.push_back(TextField(left,200,"Start"));
		textFields.push_back(TextField(left,250,"Options"));
		textFields.push_back(TextField(left,300,"Exit"));
			list<TextField>::iterator it;
		//enumerate through text field array
		for ( it=textFields.begin() ; it != textFields.end(); it++ )
		{
			//check if inside text field area
			EntityManager::getInstance()->textFieldList.push_back(&(*it));
		}
		EntityManager::getInstance()->textFieldList.push_back(new TextField(left+30,150,"Menu"));
	}
	else
	{
		//make buttons for the options screen
		EntityManager::getInstance()->textFieldList.push_back(new TextField(left+30,150,"Options"));
		textFields.push_back(TextField(left,200,"Back"));
		list<TextField>::iterator it;
		for ( it=textFields.begin() ; it != textFields.end(); it++ )
		{
			EntityManager::getInstance()->textFieldList.push_back(&(*it));
		}
	}
}


GameMenu::~GameMenu(void)
{
}

void GameMenu::handleLeftDownClick(int x,int y)
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

void GameMenu::handleMouseMoving(int x,int y)
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
int GameMenu::handleLeftUpClick(int x,int y)
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

int GameMenu::handleButton(string value)
{
	//do stuff based on which button is clicked
	if (value.compare("Start")==0)
	{
		StateManager::getInstance()->changeState(InGame);
		return 2;
	}
	if (value.compare("Back")==0)
	{
		if (StateManager::getInstance()->PrevState() == Options || StateManager::getInstance()->PrevState() == Title)	
		{	
			StateManager::getInstance()->changeState(StateManager::getInstance()->PrevState());
			GameMenu::getInstance()->changeMenu(true);
		}
		else
		{
			StateManager::getInstance()->changeState(StateManager::getInstance()->PrevState());
			return 2;
		}
		
	}
	if (value.compare("Options")==0)
	{
		StateManager::getInstance()->changeState(Options);
		GameMenu::getInstance()->changeMenu(false);
	}
	if (value.compare("Exit")==0)
	{
		return 1;
	}
	return 0;
}
