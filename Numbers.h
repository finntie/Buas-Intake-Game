#pragma once
#include "template.h"
#include "surface.h"
#include <string>
using namespace Tmpl8;

class Numbers
{
public:
	void PrintNum(Surface* screen, int numbers, vec2 pos, bool big);
	void highScoreManager(int score);
	void drawHighScore(Surface* screen);
private:
	Sprite* sprite = nullptr;
	float whatNumber = 0;
	float DivisibleNumber = 0;
	int numberSize;
	Surface* screen;
	int highestDivider;
	int devisionThing = 0;
	std::string HighScoreArray[15];
	int HighScoreNumberArray[15];
	int r = 0;
};

