#include "TextField.h"
#include "EntityManager.h"

TextField::TextField(void)
{
	loc.left=0;
	loc.top=0;
	tf_textValue="";
	changed=true;
}

TextField::TextField(int x,int y, string textValue):tf_textValue(textValue)
{
	loc.left=x;
	loc.top=y;
	changed=true;
	color=D3DXCOLOR(.5f,0.0f,0.0f,.7f);
	//EntityManager::getInstance()->textFieldList.push_back(*this);
}

TextField::~TextField(void)
{
}

string TextField::getText(void)
{
	return tf_textValue;
}
void TextField::changeField(string input)
{
	tf_textValue=input;
	changed = true;
}

void TextField::mouseDown(void)
{
	color = D3DXCOLOR(.5f,.2f,0.0f,.7f);
}

void TextField::mouseOver(bool inside)
{
	if (inside)
	{
		color=D3DXCOLOR(.7f,0.0f,0.0f,.3f);
	}
	else
	{
		color=D3DXCOLOR(.5f,0.0f,0.0f,.7f);
	}
}

void TextField::mouseUp()
{
	color=D3DXCOLOR(.5f,0.0f,0.0f,.7f);
}