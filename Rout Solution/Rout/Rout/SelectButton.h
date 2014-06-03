#pragma once
#include "MenuButton.h"

class SelectButton:
	public MenuButton
{
public:
	SelectButton(void);
	SelectButton(LPTSTR tex);
	~SelectButton(void);
};