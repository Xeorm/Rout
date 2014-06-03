#include "textTutorial.h"


textTutorial::textTutorial(void)
{
}


textTutorial::~textTutorial(void)
{
}

void textTutorial::addString(wstring input)
{

	strings.push_back(input);
	timers.push_back(3000);
}

wstring textTutorial::getText()
{
	wstring value = L"";
	list<wstring>::iterator ite;
	for (ite = strings.begin();ite != strings.end();ite++)
	{
		value.append(*ite);
		value.append(L"\n");
	}
	return value;
}

void textTutorial::update(float t)
{

	if (!timers.empty() && t < 3000.0f)
	{
	list<float>::iterator itf;
	for (itf = timers.begin();itf != timers.end();itf++)
	{
		*itf -= t;
		if (*itf < 0)
		{
			itf = timers.erase(itf);
			strings.pop_front();
			if (strings.empty())
			{
				return;
			}
		}
	}
}
}



