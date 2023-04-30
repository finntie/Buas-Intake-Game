#include "Math.h"
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include "template.h"
#include "surface.h"
#include <vector>

int RandomNumber(int Min, int Max, int seed) //Generates random number
{
	srand((time(NULL)) + seed);
	int RandomNumber = (rand() % Max) + Min;
	return RandomNumber;
}
