#include "MenuButton.h"


MenuButton::MenuButton(void)
{

}

MenuButton::MenuButton(LPCSTR tex)
{

}

MenuButton::MenuButton(int x, int y,string texture)
{
	mb_x = x;
	mb_y = y;
}

MenuButton::~MenuButton(void)
{
}

/*
	Dan Hall: interact is a virtual function that defins what action
	is called when the player's mouse interacts(left clicks)
	the button.  Can be defined to be multiple things such 
	as entering text field value or dragging
*/
void MenuButton::interact(void)
{

}

/* Mutators and Accessors*/

int MenuButton::X(void) const
{
	return mb_x;
}

int MenuButton::Y(void) const
{
	return mb_y;
}

int MenuButton::Length(void) const
{
	return mb_length;
}
int MenuButton::Width(void) const
{
	return mb_width;
}

ButtonName MenuButton::Name(void) const
{
	return name;
}
