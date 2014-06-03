#pragma once
#include <list>
#include <string>
using namespace std;
class textTutorial
{
public:
	textTutorial(void);
	~textTutorial(void);
	void update(float t);
	wstring getText();
	void addString(wstring input);
private:
	list<wstring> strings;
	list<float> timers;
};

