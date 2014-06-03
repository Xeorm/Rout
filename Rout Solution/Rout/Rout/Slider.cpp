#include "Slider.h"


Slider::Slider(void)
{
}

Slider::Slider(int x, int y, string texture, int sliderX, int sliderY, int min, int max)
{
	s_sliderX = sliderX;
	s_sliderY = sliderY;
	s_minValue = min;
	s_maxValue = max;
}

Slider::~Slider(void)
{
}

int Slider::CurrentValue(void) const
{
	return s_currentValue;
}

void Slider::interact(void)
{

}
