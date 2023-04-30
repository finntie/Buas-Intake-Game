#include "Numbers.h"
#include "surface.h"
#include "template.h"
#include <vector>
#include <cmath>
#include <fstream>
#include <string>

Sprite* numberFont(new Sprite(new Surface("assets/NumberFont.png"), 10));
Sprite* numberFontBig(new Sprite(new Surface("assets/NumberFontBig.png"), 10));

using namespace Tmpl8;

std::vector<int> numberVector;
std::string inputLine;


bool isDivisibleByTen = false;

void Numbers::PrintNum(Surface* screen, int numbers, vec2 pos, bool Big) //Prints a number to the screen with sprites
{
	numberVector.clear();
	whatNumber = numbers;
	DivisibleNumber = numbers;
	isDivisibleByTen = false;
	numberSize = 0;
	
	while (isDivisibleByTen == false) //Checks how many pieces there are in a number (in 400 there are 3 different pieces, and in 1203 there are 4).
	{
		if (floor(DivisibleNumber) != 0.0f)
		{
			DivisibleNumber /= 10;
			numberSize++;
		}
		else		
		{
			isDivisibleByTen = true;
		}	
	}
	/* **EXAMPLE**
	4275
	firsthundred = ((int)whatNumber / pow(10, numberSize - 1) * pow(10, numberSize - 1));
	secondtenth = ((int)whatNumber / pow(10, numberSize - 2) * pow(10, numberSize - 2));

	num1 = ((int)whatNumber / pow(10, numberSize));
	num2 = ((int)(whatNumber - firsthundred) / pow(10, numberSize - 1));
	num3 = ((int)(whatNumber - secondtenth) / pow(10, numberSize - 2));*/

	devisionThing = 0;
	for (int i = 1; i <= numberSize; i++) //sets a whole number (like 495) into different pieces (like 4, 9 and 5). Then it puts them directly into the vector.
	{
		numberVector.emplace_back(floor(((int)whatNumber - devisionThing) / pow(10, numberSize - i)));

		devisionThing = (floor(whatNumber / pow(10, numberSize - i)) * pow(10, numberSize - i));
	}		
			
	for (int i = 0; i < numberSize; i++) //It prints the numbers in the vector.
	{
		if (Big == true)
		{					
			numberFontBig->SetFrame(numberVector[i]);
			numberFontBig->Draw(screen, pos.x + i * 42, pos.y);				
		}
		else
		{
			numberFont->SetFrame(numberVector[i]);
			numberFont->Draw(screen, pos.x + i * 21, pos.y);
		}
		
	}
	if (numberSize == 0)
	{
		if (Big == true)
		{
			numberFontBig->SetFrame(0);
			numberFontBig->Draw(screen, pos.x, pos.y);
		}
		else
		{
			numberFont->SetFrame(0);
			numberFont->Draw(screen, pos.x, pos.y);
		}
	}
}

void Numbers::highScoreManager(int score)
{
	std::ofstream outputFile;
	std::ifstream inputFile;

	//////////////////////////
	//    Read from file	//
	//////////////////////////
	inputFile.open("Highscores.txt");
	if (inputFile.fail())
	{
		perror("Highscores.txt");
	}

	r = 0;
	while (getline(inputFile, inputLine)) 
	{
		HighScoreArray[r] = inputLine; //gets the lines in the file and sets them into the array
		r++;
	}

	for (int i = 0; i < 15; i++)
	{
		HighScoreNumberArray[i] = std::stoi(HighScoreArray[i]);
	}

   	if (score != 0)
	{
		for (int i = 0; i < 15; i++)
		{
			HighScoreNumberArray[i] = std::stoi(HighScoreArray[i]);

			if (score == HighScoreNumberArray[i])
			{
				break;
			}
			if (score > HighScoreNumberArray[i])
			{
				HighScoreArray[14] = std::to_string(HighScoreNumberArray[13]);
				for (int j = 13; j > i; j--)
				{
					HighScoreArray[j] = HighScoreArray[j - 1]; //Sets all the scores 1 down if the new score is higher than a score in the list
				}
				HighScoreNumberArray[i] = score;
				HighScoreArray[i] = std::to_string(HighScoreNumberArray[i]);
				break;
			}
			HighScoreArray[i] = std::to_string(HighScoreNumberArray[i]);

		}
	}





	//////////////////////////
	//     Save in file	    //
	//////////////////////////
	
	outputFile.open("Highscores.txt");
	if (outputFile.fail()) 
	{
		perror("Highscores.txt");
	}

	for (int i = 0; i < 15; i++)
	{
		outputFile << HighScoreArray[i] << std::endl;
	}
	outputFile.close();

}

void Numbers::drawHighScore(Surface* screen)
{

	for (int i = 0; i < 15; i++)
	{
		PrintNum(screen, HighScoreNumberArray[i], { (float)500, (float)(i * 30 + 30 ) }, false);
	}

}