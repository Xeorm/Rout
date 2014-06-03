#pragma once
#include "MenuButton.h"
#include <iostream>
#include <string> 
class TextField
{
private:
	string tf_textValue; //Dan Hall: The string value that resides in the text field
public:
	TextField(void);
	TextField(int x,int y, string textValue); //x,y refers to upperleft corner in window coordinates (not DX10 coordinates)
	~TextField(void);
	string getText(void);
	void changeField(string input);
	RECT loc;
	D3DXCOLOR color;
	bool changed;
	
	void mouseOver(bool);
	void mouseDown();
	void mouseUp();
	
};

