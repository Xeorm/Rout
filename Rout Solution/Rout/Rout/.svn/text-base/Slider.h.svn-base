#pragma once
#include "MenuButton.h"
class Slider//:
	//public MenuButton
{
private:
	int s_sliderX; //Dan Hall: The x position of the slider bar
	int s_sliderY; //Dan Hall: The y position of the slider bar
	int s_minValue; //Dan Hall: The minimum value of the slider
	int s_maxValue; //Dan Hall: The maximum value of the slider
	int s_currentValue; //Dan Hall: the current value of the slider

public:
	Slider(void);
	Slider(int x, int y, string texture, int sliderX, int sliderY, int min, int max);
	~Slider(void);
	int CurrentValue(void) const;
	virtual void interact(void);
	
};

